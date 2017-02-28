extern crate byteorder;

use std::io;
use std::io::Read;
use byteorder::{NativeEndian, ReadBytesExt};
use std::io::Cursor;
use std::str;

fn send_message() {
   let mut bytes: [u8; 4] = [0; 4];
   let mut cursor = Cursor::new(bytes);
}

fn main() {
    let mut bytes: [u8; 4] = [0; 4];
    io::stdin().read(&mut bytes).unwrap();
    let mut c = Cursor::new(bytes);
    let len = c.read_u32::<NativeEndian>().unwrap();
    println!("len: {}", len);

    // Note: read() requires pre-sized vector
    let mut buf = vec![0; len as usize];
    let mut handle = io::stdin().take(len as u64);
    let n = handle.read(&mut buf).unwrap();
    println!("n: {}", n);

    let msg = String::from_utf8(buf).unwrap();
    println!("message: {}", msg);

    if msg == "ping" {
        println!("we got ping");
        send_message();
    }
}
