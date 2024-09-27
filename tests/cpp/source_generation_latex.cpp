//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <cppad/cg.hpp>
#include <cppad/cg/lang/latex/latex.hpp>

using namespace CppAD;
using namespace CppAD::cg;

int main() {
    // use a special object for source code generation
    using CGD = CG<double>;
    using ADCG = AD<CGD>;

    /***************************************************************************
     *                               the model
     **************************************************************************/

    // independent variable vector
    CppAD::vector<ADCG> x(2);
    x[0] = 2.;
    x[1] = 3.;
    Independent(x);

    // dependent variable vector
    CppAD::vector<ADCG> y(1);

    // the model
    ADCG a = x[0] / 1. + x[1] * x[1];
    y[0] = a / 2;

    ADFun<CGD> fun(x, y);  // the model tape

    /***************************************************************************
     *                       Generate the Latex source code
     **************************************************************************/

    CodeHandler<double> handler;

    CppAD::vector<CGD> xv(x.size());
    handler.makeVariables(xv);

    CppAD::vector<CGD> vals = fun.Forward(0, xv);

    LanguageLatex<double> langLatex;
    LangLatexDefaultVariableNameGenerator<double> nameGen;

    std::ofstream texfile;
    texfile.open("algorithm.tex");

    handler.generateCode(texfile, langLatex, vals, nameGen);

    texfile.close();

    /***************************************************************************
     *                               Compile a PDF file
     **************************************************************************/
#ifdef PDFLATEX_COMPILER
    std::string dir = system::getWorkingDirectory();

    system::callExecutable(PDFLATEX_COMPILER, {"-halt-on-error", "-shell-escape",
                                               system::createPath({dir, "resources"}, "latex_template.tex")});
#endif
}