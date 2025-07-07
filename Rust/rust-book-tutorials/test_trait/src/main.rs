
trait StudentTrait
{
    fn research(&self);
}

struct Student
{
    name : String,
    age : u64,
    has_phd : bool,
}

impl StudentTrait for Student
{
    fn research(&self)
    {
        println!("Doing my research");
    }
}

fn create_student() -> Student
{
    let student = Student {
        name : String::from("Marco"),
        age : 26,
        has_phd : true
    };
    return student;
}

/**
 * @brief prints a student structure
*/
fn print_student(student : &Student)
{
    println!("Name of student is : {}, age : {}, has a phd : {}", student.name, student.age, student.has_phd);
}

fn main() {
    let ref student = create_student();
    print_student(student);

    let ref mut another_student = Student {
        name : String::from("Polo"),
        age : 33,
        has_phd : false
    };

    print_student(another_student);
    student.research();
    another_student.research();
}
