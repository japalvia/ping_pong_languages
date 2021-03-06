extern crate byteorder;
#[macro_use]
extern crate serde_json;

use std::io;
use std::io::{Read, Write};
use byteorder::{NativeEndian, ReadBytesExt, WriteBytesExt};
use std::io::Cursor;
use serde_json::Value;

fn debug(s: String) {
    writeln!(&mut std::io::stderr(), "{}", s).unwrap();
}

fn receive_message() -> String {
    let mut bytes: [u8; 4] = [0; 4];
    io::stdin().read(&mut bytes).unwrap();
    let mut c = Cursor::new(bytes);
    let len = c.read_u32::<NativeEndian>().unwrap();
    debug(format!("len: {}", len));

    // Note: read() requires pre-sized vector
    let mut buf = vec![0; len as usize];
    let mut handle = io::stdin().take(len as u64);
    handle.read(&mut buf).unwrap();

    String::from_utf8(buf).unwrap()
}

fn send_message() {
    let val = json!([
        "pong"
    ]);
    let val_str = val.to_string();
    let mut bytes = vec![];

    bytes.write_u32::<NativeEndian>(val_str.len() as u32).unwrap();
    io::stdout().write(bytes.as_slice()).unwrap();
    io::stdout().write(val_str.as_bytes()).unwrap();
    io::stdout().flush().unwrap();
}

fn main() {
    let msg = receive_message();
    let value: Value = serde_json::from_str(&msg).unwrap();
    debug(format!("value: {}", value));

    // Message from example add-on is not JSON string but just
    // a string literal.
    if value == "ping" {
        send_message();
    }
    // This is JSON array with "ping" object
    if value[0] == "ping" {
        send_message();
    }
}
