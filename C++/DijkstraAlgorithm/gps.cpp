#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

struct Place
{
    Place(const std::string& _name, float _x, float _y) :
        name(_name),
        x(_x),
        y(_y)
    {
    }

    float distance(const Place& other) const
    {
        float distance = abs(sqrt(pow(other.x - x, 2) + pow(other.y - y, 2)));
        return distance;
    }

    bool operator==(const Place& other) const
    {
        return name == other.name;
    }

    bool operator!=(const Place& other) const
    {
        return ! this->operator==(other);
    }

    std::string name;
    float x;
    float y;
};

struct DijkstraAlgorithm
{
    std::vector<Place> compute_shortest_path(const uint8_t start, const uint8_t end )
    {
        // The starting point is aready visited by definition
        visited.clear();
        visited.push_back(places[start]);
        while(true)
        {
            const auto& current_place = visited.back();
            auto remaining = compute_remaining();
            float distance = 1000.0f;
            uint8_t index_of_min_distance = 0;
            for (uint8_t i = 0 ; i < remaining.size() ; i++)
            {
                float comp_d = current_place.distance(remaining[i]);
                if (distance > comp_d)
                {
                    distance = comp_d;
                    index_of_min_distance = i;
                }
            }

            visited.push_back(remaining[index_of_min_distance]);
            if (remaining[index_of_min_distance] == places[end])
            {
                break;
            }
        }

        return visited;
    }

    std::vector<Place> compute_remaining() const
    {
        std::vector<Place> remaining;
        for (const auto& place : places)
        {
            auto found = std::find_if(visited.begin(),
                                      visited.end(),
                                      [place](const Place& current)
                                      {
                                          return place == current;
                                      });
            // This place has not been visited yet
            if (found == visited.end())
            {
                remaining.push_back(place);
            }
        }
        return remaining;
    }

    std::vector<Place> places;
    std::vector<Place> visited;
};


int main(int argc, char** argv)
{
    (void) argc;
    (void) argv;
    DijkstraAlgorithm algo;
    algo.places = {
        {"Cinema"   ,12.2, 13.6},
        {"House"    ,5.2, 17.3},
        {"School"   ,-4.2, 8.3},
        {"Library"  ,-3.98, -2.7},
        {"Stadium"  ,-7.32, 13.6}
    };

    auto shortest = algo.compute_shortest_path(0, 3);
    uint8_t index = 0;
    for (const auto& place : shortest)
    {
        std::cout << "[" << std::to_string(index) << "] : " << place.name << "\t: { " << place.x << " , " << place.y << "} " << std::endl;
        index++;
    }

    return 0;
}