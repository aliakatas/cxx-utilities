#ifndef CSV_WRITER_H
#define CSV_WRITER_H

#include <map>
#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>
#include <iomanip>

template <typename dtype_t>
void write_to_csv(const std::map<std::string, std::vector<dtype_t>>& contents, const std::string& fname) noexcept(false)
{
    std::vector<std::string> col_names; 
    for (auto& c : contents)
        col_names.push_back(c.first);
    
    size_t nrows = contents.at(col_names[0]).second.size();

    std::ofstream f(fname, std::ios::out);
    if (!f.is_open())
    {
        std::string t = std::string(__FUNCTION__) + std::string(": failed to open ") + fname + std::string(" for writing");
        throw std::runtime_error(t.c_str());
    }
    f << std::setprecision(5);

    f << ",";
    for (auto& name : col_names)
        f << name << ",";
    f << "\n";

    for (auto irow = 0; irow < nrows; ++irow)
    {
        f << irow << ",";
        for (auto& name : col_names)
            f << contents.at(name).second.at(irow) << ",";
        f << "\n";
    }
    f.close();
}


#endif // CSV_WRITER_H