extern crate byteorder;

use std::io;
use std::io::Read;
use byteorder::{NativeEndian, ReadBytesExt};
use std::io::Cursor;

fn main() {
    let mut buffer: [u8; 4] = [0; 4];
    match io::stdin().read(&mut buffer) {
        Ok(n) => {
            println!("{} bytes read", n);
            println!("bytes: {:?}", buffer);
            let mut val = Cursor::new(buffer);
            println!("bytes to int: {}", val.read_u32::<NativeEndian>().unwrap());
        }
        Err(error) => println!("error: {}", error),
    }
}
