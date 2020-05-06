#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

struct Point3
{
    Point3() = default;
    Point3(double p_x, double p_y, double p_z) : x(p_x), y(p_y), z(p_z) {}
    Point3(const Point3& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
    }
    double x = 0;
    double y = 0;
    double z = 0;
};

struct Edge3
{
    Edge3() = default;
    Edge3(const Point3& p_start, const Point3& p_end) : start(p_start), end(p_end) {}

    Point3 start;
    Point3 end;
};

struct Face
{
    Face() = default;
    Face(const vector<Point3>& vec) : points(vec) {}
    string name;
    uint64_t id = 0;
    vector<Point3> points;
};

struct Mesh
{
    Mesh(const vector<Face>& p_faces) : faces(p_faces) {}
    template<typename T>
    Face* operator[](const T parameter)
    {
        auto found_face = std::find_if(faces.begin(), faces.end(), FaceFinder<T>(parameter));
        if (found_face == faces.end())
        {
            return nullptr;
        }
        return &(*found_face);
    }

    vector<Face> faces;

    template<typename T>
    struct FaceFinder
    {
        FaceFinder(const T& p_parameter) : parameter(p_parameter) {}
        bool operator()(Face& f) const
        {
            auto id = static_cast<uint64_t>(parameter);
            return f.id == id;
        }
        T parameter;
    };


};

template<>
Face* Mesh::operator[]<const char*>(const char* parameter)
{
    auto found_face = std::find_if(faces.begin(), faces.end(), FaceFinder<string>(string(parameter)));
    if (found_face == faces.end())
    {
        return nullptr;
    }
    return &(*found_face);
}


template<>
bool Mesh::FaceFinder<string>::operator()(Face& f) const
{
    return f.name == parameter;
}

int main()
{
    Point3 a1({1,2,3});
    Point3 a2({0,21,-3});
    Point3 a3({10,2,-3});

    Point3 b1({-1,-2,-3});
    Point3 b2({2,2,2});
    Point3 b3({1,1,1});
    Face f1(vector<Point3>({a1,a2,a3}));
    f1.name = "face 1";
    f1.id = 15;
    Face f2(vector<Point3>({a1,a2,a3}));
    f2.name = "face 2";
    f2.id = 22;

    Mesh m(vector<Face>({f1,f2}));
    auto face1 = m["face 1"];
    if (face1 != nullptr)
    {
        cout << "found face 1 whose id is : " << face1->id << endl;
    }
    auto face2 = m[string("face 2")];
    if (face2 != nullptr)
    {
        cout << "found face 2 whose id is : " << face2->id << endl;
    }

    auto face1_by_id = m[15];
    if (face1_by_id != nullptr)
    {
        cout << "found face 1 with its id, whose name is : " << face1_by_id->name << endl;
    }
    auto face2_by_id = m[22];
    if (face2_by_id != nullptr)
    {
        cout << "found face 2 with its id, whose name is : " << face2_by_id->name << endl;
    }
    return 0;
}



