#include "svgfile.h"
#include "util.h"
#include <iostream>
#include <sstream>

const std::string svgHeader =
    "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
    "<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\"> "

    " <defs>"
<<<<<<< HEAD
    "<rect>"
    "<title>Hello world</title>"
    "</rect>"
=======
    "<title>Hello world</title>"
>>>>>>> Versioncool
    " </defs>";
const std::string svgEnding = "\n\n</svg>\n";

/// Effets "Boule en relief", voir donn�es � la fin de ce fichier
extern const std::string svgBallGradients;

std::set<std::string> Svgfile::s_openfiles;

bool Svgfile::s_verbose = true;

Svgfile::Svgfile(std::string _filename, int _width, int _height) :
    m_filename{_filename}, m_width{_width}, m_height{_height}
{

    if (s_verbose)
        std::cout << "Votre paysage est dans : "
                  << m_filename << std::endl;


    if ( s_openfiles.count(m_filename) )
        throw std::runtime_error( "File " + m_filename + " already open !" );

    m_ostrm.open(m_filename);

    s_openfiles.insert(m_filename);


    if (!m_ostrm)
    {
        std::cout << "Problem opening " << m_filename << std::endl;
        throw std::runtime_error("Could not open file " + m_filename );
    }

    if (s_verbose)
        std::cout << "" << std::endl;

    // Writing the header into the SVG file
    m_ostrm << svgHeader;

    m_ostrm << "width=\"" << m_width << "\" height=\"" << m_height << "\">\n\n";
}

Svgfile::~Svgfile()
{
    // Writing the ending into the SVG file
    m_ostrm << svgEnding;

    // Removing this file from the list of open files
    s_openfiles.erase(m_filename);

    // No need to explicitly close the ofstream object (automatic upon destruction)
}

// Helper templated function
template<typename T>
std::string attrib(std::string name, T val)
{
    std::ostringstream oss;
    oss << name << "=\"" << val << "\" ";
    return oss.str();
}


void Svgfile::addDisk(double x, double y, double r, std::string color)
{
    //auto tailley = std::to_string(2);
    m_ostrm << "<circle "
            << attrib("cx", x)
            << attrib("cy", y)
            << attrib("r",  r)
            << attrib("fill", color )
  //          <<attrib("transform","scale("+tailley+","+tailley+")")
            << "/>\n";
}


void Svgfile::addEllipse(double cx, double cy, double rx,double ry, double strokewidth, std::string color,std::string colorstroke)
{
    m_ostrm << "<ellipse "
            << attrib("cx", cx)
            << attrib("cy", cy)
            << attrib("rx",  rx)
            << attrib("ry",  ry)
            << attrib("fill", color )
            << attrib("stroke", colorstroke)
            <<attrib("stroke-width",strokewidth)
            << "/>\n";
}

void Svgfile::addCircle(double x, double y, double r, double ep, std::string color)
{
    m_ostrm << "<circle "
            << attrib("cx", x)
            << attrib("cy", y)
            << attrib("r",  r)
            << attrib("fill", "none")
            << attrib("stroke", color )
            << attrib("stroke-width", ep )
            << "/>\n";
}


void Svgfile::addRectangle(double x, double y, double width, double height, std::string color)
{
    m_ostrm << "<rect "
            << attrib("x", x)
            << attrib("y", y)
            << attrib("width",  width)
            << attrib("height",  height)
            << attrib("fill", color)
            <<attrib("title","Hello world")
            << "/>\n";
}

void Svgfile::addLine(double x1, double y1, double x2, double y2, std::string color)
{
    m_ostrm << "<line "
            << attrib("x1", x1)
            << attrib("y1", y1)
            << attrib("x2", x2)
            << attrib("y2", y2)
            << attrib("stroke", color)
            << "/>\n";
}
void Svgfile::addRoute(double x1, double y1, double x2, double y2,double ep, std::string color)
{
    m_ostrm << "<line "
            << attrib("x1", x1)
            << attrib("y1", y1)
            << attrib("x2", x2)
            << attrib("y2", y2)
            << attrib("stroke", color)
            << attrib("stroke-width", ep )
            << "/>\n";
}
/*void Svgfile::addroute(double x1, double y1, double x2, double y2, std::string color)
{
    m_ostrm << "<rect "
            << attrib("x", x)
            << attrib("y", y)
            << attrib("width",  width)
            << attrib("height",  height)
            << attrib("fill", color)
            << "/>\n";

}*/



void Svgfile::addText(double x, double y, std::string text, std::string color)
{
    /// <text x="180" y="60">Un texte</text>
    m_ostrm << "<text "
            << attrib("x", x)
            << attrib("y", y)
            << attrib("fill", color)
            << ">" << text << "</text>\n";
}

void Svgfile::addText(double x, double y, double val, std::string color)
{
    std::ostringstream oss;
    oss << val;
    addText(x, y, oss.str(), color);
}

void Svgfile::addGrid(double span, bool numbering, std::string color)
{
    double y=0;
    while (y<=m_height)
    {
        addLine(0, y, m_width, y, color);
        if (numbering)
            addText(5, y-5, y, color);
        y+=span;
    }

    double x=0;
    while (x<=m_width)
    {
        addLine(x, 0, x, m_height, color);
        if (numbering)
            addText(x+5, 15, x, color);
        x+=span;
    }
}
std::string Svgfile::makeRGB(int r, int g, int b)
{
    std::ostringstream oss;
    oss << "rgb(" << r << "," << g << "," << b << ")";
    return oss.str();
}
