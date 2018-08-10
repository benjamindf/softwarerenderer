#include <regex>
#include <iostream>
#include <iterator>
#include <sstream>
#include <glm/glm.hpp>
#include <exception>
#include <functional>

class RasterBox
{
    private:
    glm::ivec2 min;
    glm::ivec2 max;
    public:
    RasterBox(const glm::ivec2& min, const glm::ivec2& max) : min(min) , max(max) {}
   class iterator {
        public:
        RasterBox* box;
        glm::ivec2 current;
        iterator(RasterBox* box, glm::ivec2 current) : box(box), current(current) {}
        iterator(const iterator& other) : box(other.box), current(other.current) {}
        iterator operator=(const iterator& other) {box = other.box; current = other.current; return *this;}
        ~iterator() {}
        glm::ivec2 operator*() {return current;}
        iterator operator++() 
        { 
            if(current.x == box->max.x)
            {
                current.x = box->min.x;
                current.y++;
            }
            else 
            {
                current.x++;
            }
            return *this;
        }
        bool operator==(const iterator& other) { return current == other.current; }
        bool operator!=(const iterator& other) { return !(*this == other); }
    };
    iterator begin() { return iterator(this, min);}
    iterator end() { return iterator(this, glm::ivec2(min.x, max.y+1));}
};



std::istream& operator>>(std::istream& stream, glm::vec3& v)
{
	return stream >> v.x >> v.y >> v.z;	
}

std::istream& operator>>(std::istream& stream, const char(&lit))
{
	char read;
	stream >> read;
	if(read != lit)
	{
	    stream.setstate(std::ios::failbit);	
	}
	
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const glm::vec3& v)
{
	return stream << "(" << v.x << "," << v.y << "," << v.z << ")";
}

struct AttribIndex
{
	size_t pos_index;	
	size_t uv_index;	
	size_t norm_index;	
};

std::ostream& operator<<(std::ostream& stream, const AttribIndex& ai)
{
	return stream << "[" << ai.pos_index << ":" << ai.uv_index << ":" << ai.norm_index << "]";
}


void doThing(const std::string &str)
{
	if(str.length() > 0) 
	{
		std::stringstream ss(str);
		std::string type;
		ss >> type;
		ss.exceptions(std::ios::failbit); 

		if(type == "f")
		{
			AttribIndex a,b,c;
			ss >> a.pos_index >> '/' >> a.uv_index >> '/' >> a.norm_index; 
			ss >> b.pos_index >> '/' >> b.uv_index >> '/' >> b.norm_index; 
			ss >> c.pos_index >> '/' >> c.uv_index >> '/' >> c.norm_index; 

			std::cout <<  "Face: " << a << " , " << b  << " , " << c << "\n";
				
		}
		else if(type == "v")
		{
			glm::vec3 v;
			ss >> v;
			std::cout << "Position: " << v << "\n";
		}
		else if(type == "vt")
		{
			glm::vec3 v;
			ss >> v;
			std::cout << "UV: " <<  v << "\n";
		}
		else if(type == "vn")
		{
			glm::vec3 v;
			ss >> v;
			std::cout << "Normal: " << v << "\n";
		}
	}

}


int main()
{

    
    RasterBox r{glm::ivec2(10,10), glm::ivec2(30,50)};
    for(auto p : r)
    {
        std::cout << "(" << p.x << "," << p.y << ")" << "\n";
    }
     

    //Grab every character from
//    std::stringstream ss;
//    std::noskipws(std::cin);
//    std::copy(std::istream_iterator<char>(std::cin),
//              std::istream_iterator<char>(),
//              std::ostream_iterator<char>(ss));
//
//    std::string s = ss.str();
//    std::regex re("\n");
//
//                  //[](const std::string& a) { std::cout << a << " <--- one-line \n";});
//    //An iterator which will give all tokens, (aka lines) in string
//    try 
//    {
//        std::for_each(std::sregex_token_iterator(s.begin(), s.end(), re, -1),
//                      std::sregex_token_iterator(),
//                      doThing);
//    }
//
//    catch(std::ios_base::failure f)
//    {
//        std::cout << "Error, malformed obj file:\n";
//		std::cout << f.what() << "\n";
//    }

}
