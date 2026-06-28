use esp_idf_svc::hal::prelude::*;
use esp_idf_svc::hal::gpio::*;

fn main() -> anyhow::Result<()> {
    esp_idf_svc::sys::link_patches();
    esp_idf_svc::log::EspLogger::initialize_default();

    let peripherals = Peripherals::take().unwrap();

    // Configure GPIO23 and GPIO22 as outputs
    let mut io23 = PinDriver::output(peripherals.pins.gpio23)?;
    let mut io22 = PinDriver::output(peripherals.pins.gpio22)?;

    // Drive them high
    io23.set_high()?;
    io22.set_high()?;

    log::info!("GPIO23 and GPIO22 set HIGH");

    // Keep the task alive (otherwise main returns and your program may end)
    loop {
        std::thread::sleep(std::time::Duration::from_secs(1));
    }
}