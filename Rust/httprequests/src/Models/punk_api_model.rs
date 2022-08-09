use serde::{Deserialize, Serialize};
use std::fs;

#[derive(Serialize, Deserialize, Debug)]
pub struct Item<T>
{
    value : T,
    unit : String
}

#[derive(Serialize, Deserialize, Debug)]
pub struct MashingStep
{
    temp : Item<u64>,
    duration : Option<u64>
}

#[derive(Serialize, Deserialize, Debug)]
pub struct FermentationStep
{
    temp : Item<u64>
}

#[derive(Serialize, Deserialize, Debug)]
pub struct Method
{
    mash_temp : Vec<MashingStep>,
    fermentation : FermentationStep,
    twist : Option<String>
}

#[derive(Serialize, Deserialize, Debug)]
pub struct Malt
{
    name : String,
    amount : Item<f64>
}

#[derive(Serialize, Deserialize, Debug)]
pub struct Hop
{
    name : String,
    amount : Item<f64>,
    add : String ,
    attribute : String
}

#[derive(Serialize, Deserialize, Debug)]
pub struct Ingredients
{
    malt : Vec<Malt>,
    hops : Vec<Hop>,
    yeast : String
}

#[derive(Serialize, Deserialize, Debug)]
pub struct BeerModel
{
    id : u64,
    name : String,
    tagline : String,
    first_brewed : String,
    description : String ,
    image_url : String,
    abv : f64,
    ibu : Option<f64>,
    target_fg : f64,
    target_og : f64,
    ebc : Option<f64>,
    srm : Option<f64>,
    ph : Option<f64>,
    attenuation_level : f64,
    volume : Item<f64>,
    boil_volume : Item<f64>,
    method : Method,
    ingredients : Ingredients,
    food_pairing : Vec<String>,
    brewers_tips : String,
    contributed_by : String
}

impl Default for BeerModel {
    fn default() -> Self {
        BeerModel {
            id : 1,
            name : String::from("test"),
            tagline : String::from("test"),
            first_brewed : String::from("test"),
            description : String::from("test"),
            image_url : String::from("test"),
            abv : 12.0,
            ibu : Some(14.0),
            target_fg : 1004.0,
            target_og : 1044.0,
            ebc : Some(100.0),
            srm : Some(15.0),
            ph : Some(4.5),
            attenuation_level : 75.0,
            volume : Item {
                value : 20.0,
                unit : String::from("litres")
            },
            boil_volume : Item {
                value : 20.0,
                unit : String::from("litres")
            },
            method : Method {
                mash_temp : Vec::from([
                     MashingStep {
                        temp : Item {
                            value : 64,
                            unit : String::from("celsius")
                        },
                        duration : Some(74)
                    }
                ]),
                fermentation : FermentationStep {
                    temp : Item {
                        value : 19,
                        unit : String::from("celsius")
                    }
                },
                twist : None
            },
            ingredients : Ingredients {
                malt: Vec::from([
                        Malt {
                            amount : Item { value: 3.3, unit: String::from("kilograms") },
                            name : String::from("Maris Otter Extra Pale")
                        }
                    ]
                ),
                hops: Vec::from([
                    Hop {
                        name : String::from("Fuggles"),
                        amount : Item {
                            value : 25.0,
                            unit : String::from("grams")
                        },
                        add : String::from("middle"),
                        attribute : String::from("flavour")
                    }
                ]),
                yeast: String::from("test")
            },
            food_pairing : Vec::from([String::from("")]),
            brewers_tips : String::from(""),
            contributed_by : String::from("")
        }
    }
}

impl BeerModel {
    pub fn to_file(self, filepath : &std::path::Path) -> std::io::Result<()>
    {
        // let file = std::fs::File::options()
        // .write(true)
        // .create(true)
        // .open(filepath);

        fs::write(filepath, serde_json::to_string_pretty(&self).unwrap())
    }
}