//use std::collections::HashMap;
//use std::collections::hash_map::Entry::{Occupied, Vacant};
use std::time::Instant;
use std::env;

pub fn fib(n: i32) -> u64 {
    if n < 0 {
        panic!("{} is negative!", n);
    }
    match n {
        //0 => panic!("zero is not a right argument to fibonacci_reccursive()!"),
        0 => 0,
        1 => 1,
        //1 | 2 => 1,
        //3 => 2,
        //50    => 12586269025,
        _ => fib(n - 1) + fib(n - 2),
    }
}


fn main() {
	println!("**************************************** RUST ****************************************");
        let args: Vec<String> = env::args().collect();
        let s = &args[1];
        
        let n = match s.parse::<i32>() {
            Ok(x) => x, 
            Err(_e) => 10, 
        };
        
        let now = Instant::now();
        println!("fib({0})={1}", n, fib(n));
        let elapsed = now.elapsed();
        println!("Time: {:.2?} !!", elapsed);
}

