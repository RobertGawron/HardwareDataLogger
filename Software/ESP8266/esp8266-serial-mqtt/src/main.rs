#![no_std]
#![no_main]

use esp8266_hal::{ prelude::*, target::Peripherals };
use panic_halt as _;


#[xtensa_lx_rt::entry]
fn main() -> ! {
    let peripherals = Peripherals::take().unwrap();
    let pins = peripherals.GPIO.split();
    

    let mut led = pins.gpio2.into_push_pull_output();
    led.set_high().unwrap();

    let (mut timer1, _) = peripherals.TIMER.timers();
    

    loop {
        led.toggle().unwrap();
        timer1.delay_ms(500);
        
    }
}
