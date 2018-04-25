#include <iostream>
#include "../vector/my_vector.h"

const double step = 0.01;

void MakePlot (Vector <double>& dots);

int main()
{
    try
    {
        std::ifstream input("dots.txt");
        int number = 0;
        input >> number;

        Vector <double> dots(number);

        for (int i = 0; i < number; i++)
        {
            input >> dots[i];
        }

        input.close();

        dots.set_interpolation(CATROM);

        MakePlot (dots);
    }

    catch (mega_exception* exception)
    {
        std::ofstream log("log.txt");
        log << exception;
        log.close();

        std::cout << "Read log.txt\n";
        abort ();
    }

    system ("pdflatex plot.tex");
    return 0;
}

void MakePlot (Vector <double>& dots)
{
    std::ofstream output("plot.tex");

    output << "\\documentclass[a4paper,12pt]{article}\n";
    output << "\\usepackage{float}\n";
    output << "\\usepackage{pgfplots}\n";
    output << "% Preamble: \\pgfplotsset{width=1cm,compat=newest}\n";
    output << "\\begin{document}\n";
    output << "\\begin{tikzpicture}\n";
    output << "\\begin{axis}[height=15cm,width=15cm,grid=major]\n";
    output << "\\addlegendentry{gpaphic}\n";
    output << "\\addplot[color = blue, mark = * ] coordinates {\n";

    try
    {
        for (double i = 0; i < dots.Size() - 1; i += step)
            output << '(' << i << ',' << dots[i] << ")\n";
    }

    catch (mega_exception* exception)
    {
        MAKE_EXCEPTION("Something happened during making dots", ER_DOT, exception);
    }

    output << "};\n\n";
    output << "\\addlegendentry{dots}\n";
    output << "\\addplot[color = red, mark = * ] coordinates {\n";

    try
    {
        for (int i = 0; i < dots.Size(); i++)
            output << '(' << i << ',' << dots[i] << ")\n";
    }

    catch (mega_exception* exception)
    {
        MAKE_EXCEPTION("Something happened during making dots", ER_DOT, exception);
    }

    output << "};\n\n";
    output << "\\end{axis}\n";
    output << "\\end{tikzpicture}\n";
    output << "\\end{document}\n";

    output.close();
}
