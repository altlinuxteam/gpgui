#if !defined(__GPTBACKEND_REG_H)
#define __GPTBACKEND_REG_H 1

#include <string>

namespace reg {

class reg_writer {
public:
    reg_writer(std::string file_path);
};

} /* namespace reg */

#endif /* __GPTBACKEND_REG_H */

