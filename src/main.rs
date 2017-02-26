extern crate byteorder;

use std::io;
use std::io::Read;
use byteorder::{NativeEndian, ReadBytesExt};
use std::io::Cursor;
use std::str;

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

    let mut data = Vec::new();
    match io::stdin().read_to_end(&mut data) {
        Ok(n) => {
            println!("{} bytes read", n);
            let s = String::from_utf8(data).expect("Found invalid UTF-8");
            println!("{}", s);
        }
        Err(error) => println!("error: {}", error),
    }
}
