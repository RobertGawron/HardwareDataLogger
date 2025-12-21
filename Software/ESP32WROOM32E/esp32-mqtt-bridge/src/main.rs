use esp_idf_svc::wifi::EspWifi;
use esp_idf_svc::nvs::EspDefaultNvsPartition;
use esp_idf_svc::eventloop::EspSystemEventLoop;
use esp_idf_hal::prelude::Peripherals;
use std::thread;
use std::time::Duration;

fn main() -> anyhow::Result<()> {
    // 1. Initialize the system
    esp_idf_svc::sys::link_patches();

        // Bind the log crate to the ESP Logging facilities
    esp_idf_svc::log::EspLogger::initialize_default();

    let peripherals = Peripherals::take()?;
    let sys_loop = EspSystemEventLoop::take()?;
    let nvs = EspDefaultNvsPartition::take()?;

    println!("ESP32 Starting...");

    // 2. Next: Add WiFi and MQTT logic here
    // You can now use standard Rust threads and networking!
    loop {
        println!("Heartbeat from ESP32-WROOM-32E");
        thread::sleep(Duration::from_secs(5));
    }
}