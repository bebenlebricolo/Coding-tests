

#[path = "./Models/punk_api_model.rs"]
mod punk_api_model;

use punk_api_model::BeerModel;
use std::fs;
use reqwest::{self, Error, Response, header::{CONTENT_TYPE, ACCEPT}};

const PUNK_API_ROOT : &str = "https://api.punkapi.com/v2/";
const PUNK_API_BEERS_CONTROLLER : &str = "beers";

// enum PunkApiParamKind
// {
//     abv_gt,
//     abv_lt,
//     ibu_gt,
//     ibu_lt,
//     ebc_gt,
//     ebv_lt,
//     beer_name,
//     yeast,
//     brewed_before,
//     brewed_after,
//     hops,
//     malt,
//     food,
//     ids
// }

// union PunkApiParamValue
// {
//     str : [char; 50],
//     number : f64
// }

// struct PunkApiParams
// {
//     kind : PunkApiParamKind,
//     value : PunkApiParamValue
//}


struct PunkApiClient
{
    http_client : reqwest::Client
}


impl PunkApiClient
{
    fn create_new(client : reqwest::Client) -> PunkApiClient
    {
        let client = PunkApiClient {
            http_client : client
        };
        return client
    }

    async fn get_all_beers(self) -> Result<Response, Error>
    {
        let url = PUNK_API_ROOT.to_owned() + PUNK_API_BEERS_CONTROLLER ;
        let response = self.http_client.get(url)
                                                              .header(CONTENT_TYPE, "application/json")
                                                              .header(ACCEPT, "application/json")
                                                              .send()
                                                              .await;
        return response;
    }
}



#[tokio::main]
async fn main() {
    let default_beer = BeerModel::default();
    let path = std::path::Path::new("test.json");

    default_beer.to_file(&path).expect("Could not write default beer to disk");

    let reqwest_client = reqwest::Client::new();
    let api_client = PunkApiClient::create_new( reqwest_client);

    let response = api_client.get_all_beers().await.unwrap();
    let mut parsed_objects : Vec<punk_api_model::BeerModel> = Vec::new();

    match response.status() {
        reqwest::StatusCode::OK => {
            match response.json::<Vec<punk_api_model::BeerModel>>().await {
                Ok(parsed) =>  {
                    println!("Success !");
                    parsed_objects = parsed;
                },
                Err(origin) => println!("Hm, the response didn't match the shape we expected. Got : {:?}", origin )
            };
        }
        reqwest::StatusCode::UNAUTHORIZED => {
            println!("Need to grab a new token");
        }

        other => {
            panic!("Uh oh! Something unexpected happened: {:?}", other);
        }
    };

    fs::write(std::path::Path::new("page1.json"), serde_json::to_string_pretty(&parsed_objects).unwrap()).expect("Could not write json file to disk");

}
