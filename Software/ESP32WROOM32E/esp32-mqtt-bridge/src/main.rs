use esp_idf_svc::wifi::EspWifi;
use esp_idf_svc::nvs::EspDefaultNvsPartition;
use esp_idf_svc::eventloop::EspSystemEventLoop;
use esp_idf_hal::prelude::Peripherals;
use esp_idf_svc::mqtt::client::MqttClientConfiguration;
use std::thread;
use std::time::Duration;
use esp_idf_svc::wifi::BlockingWifi;
//use heapless::String;
use std::convert::TryInto;
use esp_idf_svc::mqtt::client::EspMqttClient;
use esp_idf_svc::mqtt::client::QoS;
use toml_cfg::toml_config;
use esp_idf_hal::uart::{UartDriver, config::Config as UartConfig};
 use esp_idf_hal::units::Hertz;
 use esp_idf_hal::delay::TickType;

// 1. Define the Config Structure
// The macro looks for a file named "cfg.toml" by default
#[toml_config]
pub struct Config {
    #[default("")]
    wifi_ssid: &'static str,
    #[default("")]
    wifi_psk: &'static str,
    #[default("")]
    mqtt_url: &'static str,
}

fn main() -> anyhow::Result<()> {
    // 1. Initialize the system
    esp_idf_svc::sys::link_patches();

        // Bind the log crate to the ESP Logging facilities
    esp_idf_svc::log::EspLogger::initialize_default();

    let peripherals = Peripherals::take()?;
    let sys_loop = EspSystemEventLoop::take()?;
    let nvs = EspDefaultNvsPartition::take()?;

    println!("ESP32 Starting...");

    // conf is in cfg.toml
    let app_config = CONFIG;

    // 1. Connect to Wi-Fi
    // Blocking means it will block till the whoe wifi stack is initialized
    // It is a wrapper, under the hood the whole initialization is event based and non blocking
    // but we dont need that and blocking approach is easssier
    let mut wifi = BlockingWifi::wrap(
        EspWifi::new(peripherals.modem, sys_loop.clone(), Some(nvs))?,
        sys_loop,
    )?;
    
    println!("Connecting to Wi-Fi: {}", app_config.wifi_ssid);
connect_wifi(&mut wifi, app_config.wifi_ssid, app_config.wifi_psk)?;

    // 2. Configure MQTT
    // Replace "192.168.1.50" with your broker's IP
    let mqtt_config = MqttClientConfiguration {
        client_id: Some("esp32-bridge"),
        ..Default::default()
    };

    let (mut client, mut connection) =
        EspMqttClient::new(app_config.mqtt_url, &mqtt_config)?;

    // 3. Spawn a thread to handle MQTT events (required)
    // MQTT requires a constant "pulse" to process incoming acknowledgments (ACKs) and Keep-Alive pings.
    thread::spawn(move || {
        while let Ok(event) = connection.next() {
            log::info!("[MQTT Event] {:?}", event.payload());
        }
    });


let uart_config = UartConfig::default().baudrate(Hertz(9600));
    // UART2 on custom pins
    let mut uart2 = UartDriver::new(
        peripherals.uart2,
        peripherals.pins.gpio17,  // TX
        peripherals.pins.gpio16,  // RX
        Option::<esp_idf_hal::gpio::Gpio0>::None,
        Option::<esp_idf_hal::gpio::Gpio0>::None,
        &uart_config,
    )?;


    let mut buf = [0u8; 256];


    // 2. Next: Add WiFi and MQTT logic here
    // You can now use standard Rust threads and networking!
    loop {
        println!("Heartbeat from ESP32-WROOM-32E");

            let payload = "Hello from ESP32!";
        client.publish("esp32/bridge/status", QoS::AtLeastOnce, false, payload.as_bytes())?;
        log::info!("Published: {}", payload);
        

         match uart2.read(&mut buf, TickType::new_millis(100).ticks()) {
            Ok(bytes_read) if bytes_read > 0 => {
                log::info!("Received {} bytes: {:?}", bytes_read, &buf[..bytes_read]);
                
                // Echo back
                uart2.write(&buf[..bytes_read])?;
            }
            _ => {
                //FreeRtos::delay_ms(10);
                 thread::sleep(Duration::from_secs(5));
            }
        }


       // thread::sleep(Duration::from_secs(5));
    }
}

fn connect_wifi(
    wifi: &mut BlockingWifi<EspWifi<'static>>, 
    ssid: &str, 
    password: &str
) -> anyhow::Result<()> {
    
    let wifi_configuration = embedded_svc::wifi::Configuration::Client(
        embedded_svc::wifi::ClientConfiguration {
            ssid: ssid.try_into().map_err(|_| anyhow::anyhow!("SSID too long"))?,
            password: password.try_into().map_err(|_| anyhow::anyhow!("Password too long"))?,
            ..Default::default()
        },
    );

    wifi.set_configuration(&wifi_configuration)?;

    wifi.start()?;
    wifi.connect()?;
    wifi.wait_netif_up()?;

    log::info!("Wi-Fi Connected successfully to {}!", ssid);
    Ok(())
}