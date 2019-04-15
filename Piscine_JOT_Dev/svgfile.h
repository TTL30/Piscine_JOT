#ifndef SVGFILE_H_INCLUDED
#define SVGFILE_H_INCLUDED

#include <string>
#include <fstream>
#include <set>
#include "Couleur.h"
#include "util.h"

constexpr char defcol[] = "black";
class Svgfile
{
public:
    Svgfile(std::string _filename = "output.svg", int _width=1000, int _height=800);
    ~Svgfile();
    void addDisk(double x, double y, double r, std::string color=defcol);
    void addEllipse(double cx, double cy, double rx,double ry,double strokewidth, std::string color=defcol,std::string colorstroke=defcol);
    void addCircle(double x, double y, double r, double ep, std::string color=defcol);

    void addRectangle(double x, double y, double width, double height, std::string colorFill);
    void addLine(double x1, double y1, double x2, double y2, std::string color=defcol);
    void addText(double x, double y, std::string text, std::string color=defcol);
    void addText(double x, double y, double val, std::string color=defcol);
    //void addArcgauche(int x, int y, std::string color, int epaisseur);
    void addGrid(double span=100.0, bool numbering=true, std::string color="lightgrey");
    void addCircleOppacite(double x, double y, double r,double oppa, std::string color);

    static std::string makeRGB(int r, int g, int b);

    /// Type non copiable
    Svgfile(const Svgfile&) = delete;
    Svgfile& operator=(const Svgfile&) = delete;

    static bool s_verbose;

private:
    std::string m_filename;
    std::ofstream m_ostrm;
    int m_width;
    int m_height;

    // Pour éviter les ouverture multiples
    static std::set<std::string> s_openfiles;
};



#endif // SVGFILE_H_INCLUDED



