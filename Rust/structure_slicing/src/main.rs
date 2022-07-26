struct User {
    active : bool,
    username : String,
    email : String,
    sign_in_count : u64
}

fn print_user(user : &User)
{
    println!("User name = {}", user.username);
    println!("User email = {}", user.email);
    println!("User is active? = {}", user.active);
    println!("User sign in count = {}", user.sign_in_count);
}

fn main() {
    println!("Hello, world!");
    let user1 = User {
        email : String::from("toto"),
        active : true,
        username : String::from("toto"),
        sign_in_count : 32
    };

    print_user(&user1)
}
