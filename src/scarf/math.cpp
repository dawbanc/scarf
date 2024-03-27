//----------------------------------------------------------------
// Project:                scarf
// Author:                 dawbanc
// Date (yy/mm/dd):        24/03/07
// Notes:
// For changes view git history
//----------------------------------------------------------------

#include "math.h"
#include <string>

class Math {

private:


public:

    std::string parseMathString(std::string inputMath);

};

std::string Math::parseMathString(std::string inputMath){
    std::string outputValue;

        try {
        // Enhanced regular inputMath to handle multiple consecutive operators
        std::regex pattern(R"(\d+|\(|\)|[a-zA-Z_]\w*|\+|-|\*|/|char|int)");
        for (std::sregex_iterator it(inputMath.begin(), inputMath.end(), pattern), end; it != end; ++it) {
            std::string token = it->str();

            if (std::isdigit(token[0])) {  // Numerical literal
                outputValue += token;
            } else if (token == "+" || token == "-" || token == "*" || token == "/") {  // Simple operator
                outputValue += token;
            } else if (token == "(") {  // Left parenthesis
                outputValue += token;
            } else if (token == ")") {  // Right parenthesis
                outputValue += token;
            } else if (token == "char" || token == "int") {  // Type cast
                outputValue += token + "(";
            } else {  // Variable or unknown token
                // Check for type cast context
                if (outputValue.size() >= 4 && outputValue.substr(outputValue.size() - 4) == "int(") {
                    outputValue += "int(" + variables.at(token) + ")";
                } else if (outputValue.size() >= 5 && outputValue.substr(outputValue.size() - 5) == "char(") {
                    outputValue += "char(" + variables.at(token) + ")";
                } else {
                    outputValue += variables.at(token);
                }
            }
        }

        // Evaluate the parsed inputMath (assuming valid mathematical syntax)
        outputValue = std::to_string(std::eval(outputValue));
    } catch (const std::exception& e) {
        std::cerr << "Error parsing or evaluating inputMath: " << e.what() << std::endl;
        outputValue = "";
    }h

    return outputValue;
}

