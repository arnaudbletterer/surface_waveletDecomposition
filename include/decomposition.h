#ifndef DECOMPOSITION_H
#define DECOMPOSITION_H

#include <QImage>

#include <vector>

namespace CGoGN
{
namespace SCHNApps
{

enum Axis
{
    HORIZONTAL=0,
    VERTICAL
};

class NQRgb
{
public:
    NQRgb(int red=0, int green=0, int blue=0)
        : r(red), g(green), b(blue)
    {}

    ~NQRgb()
    {}

    int getRed() { return r; }
    void setRed(int red) { r = red; }

    int getGreen() { return g; }
    void setGreen(int green) { g = green; }

    int getBlue() { return b; }
    void setBlue(int blue) { b = blue; }
private:
    int r, g, b;
};

class Decomposition
{
public:
    Decomposition(const int x, const int y, const short int level, Decomposition* parent = NULL)
        : m_image(),
          m_correction_x(x), m_correction_y(y),
          m_horizontal_correction(x*y), m_vertical_correction(x*y),
          m_child(NULL),
          m_parent(parent),
          m_level(level)
    {
    }

    ~Decomposition()
    {
        if(m_child)
        {
            delete m_child;
        }
    }

    QImage& getImage() { return m_image; }
    void setImage(const QImage& image) { m_image = image; }

    int getCorrectionX() { return m_correction_x; }
    int getCorrectionY() { return m_correction_y; }

    NQRgb& getHorizontalCorrection(const int x, const int y)
    {
        if(x < m_correction_x && y < m_correction_y)
        {
            return m_horizontal_correction[x+y*m_correction_x];
        }
    }
    void setHorizontalCorrection(const int x, const int y, const NQRgb& correction)
    {
        if(x < m_correction_x && y < m_correction_y)
        {
            m_horizontal_correction[x+y*m_correction_x] = correction;
        }
    }

    NQRgb& getVerticalCorrection(const int x, const int y)
    {
        if(x < m_correction_x && y < m_correction_y)
        {
            return m_vertical_correction[x+y*m_correction_x];
        }
    }
    void setVerticalCorrection(const int x, const int y, const NQRgb& correction)
    {
        if(x < m_correction_x && y < m_correction_y)
        {
            m_vertical_correction[x+y*m_correction_x] = correction;
        }
    }

    Decomposition* getChild() { return m_child; }
    Decomposition* addChild()
    {
        if(!m_child)
        {
            m_child = new Decomposition(m_correction_x/2, m_correction_y/2, m_level+1, this);
            return m_child;
        }
        CGoGNerr << "Analysis already done for level " << m_level << CGoGNendl;
        return this;
    }

    Decomposition* getParent() { return m_parent; }

    short int getLevel() { return m_level; }

private:
    QImage m_image;
    int m_correction_x, m_correction_y;
    std::vector<NQRgb> m_horizontal_correction;
    std::vector<NQRgb> m_vertical_correction;
    Decomposition* m_child;
    Decomposition* m_parent;
    short int m_level;
};

}
}

#endif // DECOMPOSITION_H
