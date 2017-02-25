use std::io::{self, Read};

fn main() {
    fn read_input() -> io::Result<String> {
        let mut buffer = String::new();
        try!(io::stdin().read_to_string(&mut buffer));
        Ok(buffer)
    }

    let buf = read_input();
    println!("got input: {}", buf);

}
