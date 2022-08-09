use std::u64;
use std::fs;
use std::io::Write;

/**
 * Pixel structure, represents a pixel in a 3D space (x,y,z coordinates) and it carries a value
 */
struct Pixel
{
    x : u64,
    y : u64,
    z : u64,
    val : f64
}

/**
 * @brief Image structure represents a 3D image
 */
struct Image
{
    name : String,
    pixels : Vec<Pixel>
}

/**
 * @brief Pixel implementations
 */
impl Pixel
{
    fn to_binary(&self) -> [u8 ; 32]
    {
        let mut buffer : [u8; 32] = [0 ; 32];
        buffer[0..8].clone_from_slice(&self.x.to_be_bytes());
        buffer[8..16].clone_from_slice(&self.y.to_be_bytes());
        buffer[16..24].clone_from_slice(&self.z.to_be_bytes());
        buffer[24..32].clone_from_slice(&self.val.to_be_bytes());
        return buffer;
    }

    fn to_bin_file(&self, path : &std::path::Path ) -> std::io::Result<()>
    {
        let file = std::fs::File::options()
            .write(true)
            .create(true)
            .open(path)?;
        let mut buffer = std::io::BufWriter::new(file);

        let data = self.to_binary();
        buffer.write(&data).expect("Could not write binary to filestream");

        return Ok(());
    }
}

impl Image
{
    fn write_to_bin_file(&self, path : &std::path::Path) -> std::io::Result<()>
    {
        let file = std::fs::File::options()
            .write(true)
            .create(true)
            .open(path)?;
        let mut buffer = std::io::BufWriter::new(file);

        buffer.write(&self.name.as_bytes()).unwrap();
        for pixel in &self.pixels
        {
            buffer.write(&pixel.to_binary()).unwrap();
        }

        return Ok(());
    }
}


fn initialize_image(image : &mut Image) -> ()
{
    let _  = &image.pixels.clear();
    for i in 0..128
    {
        for j in 0..128
        {
            for k in 0..128
            {
                let pixel = Pixel {
                    x : i,
                    y : j,
                    z : k,
                    val : 0.1 * ( i * j * k + 1) as f64
                };
                let _ = &image.pixels.push(pixel);
            }
        }
    }
}

fn main() -> () {
    let pixel = Pixel { x : 12, y : 23, z : 65, val : 0.253};
    let pixel_output_filepath = std::path::Path::new("data/binary_pixel.bin");
    let image_output_filepath = std::path::Path::new("data/binary_image.bin");
    if !pixel_output_filepath.parent().unwrap().exists()
    {
        fs::create_dir_all(pixel_output_filepath.parent().unwrap()).expect("Could not create output data directory for saving");
    }

    let err = pixel.to_bin_file(pixel_output_filepath);
    match err
    {
        Ok(()) => println!("Sucessfully written down file !"),
        Err(e) => println!("Could not write file to {} because {}", pixel_output_filepath.to_str().unwrap(), &e.to_string())
    };

    let mut image = Image {name : String::from("Test"), pixels : Vec::new() };
    initialize_image(&mut image);

    image.write_to_bin_file(image_output_filepath).unwrap();
}
