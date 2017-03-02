extern crate byteorder;
extern crate serde_json;

use std::io;
use std::io::{Read, Write};
use byteorder::{NativeEndian, ReadBytesExt, WriteBytesExt};
use std::io::Cursor;
use serde_json::Value;

fn send_message() {
   // let mut c = Cursor::new(bytes);

   let msg = "pong";

   let mut bytes = vec![];
   bytes.write_u32::<NativeEndian>(msg.len() as u32).unwrap();
   io::stdout().write(bytes.as_slice()).unwrap();
   io::stdout().write(msg.as_bytes()).unwrap();
   io::stdout().flush().unwrap();
}

fn debug(s: String) {
    writeln!(&mut std::io::stderr(), "{}", s).unwrap();
}

fn main() {
    let mut bytes: [u8; 4] = [0; 4];
    io::stdin().read(&mut bytes).unwrap();
    let mut c = Cursor::new(bytes);
    let len = c.read_u32::<NativeEndian>().unwrap();
    debug(format!("len: {}", len));

    // Note: read() requires pre-sized vector
    let mut buf = vec![0; len as usize];
    let mut handle = io::stdin().take(len as u64);
    handle.read(&mut buf).unwrap();

    let msg = String::from_utf8(buf).unwrap();
    debug(format!("message: {}", msg));

    let value: Value = serde_json::from_str(&msg).unwrap();
    debug(format!("value: {}", value));
    debug(format!("json test: {}", value["foo"]));

    /*
    if msg == "ping" {
        // println!("we got ping");
        send_message();
    }
*/
}
