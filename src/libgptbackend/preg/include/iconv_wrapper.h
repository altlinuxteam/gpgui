#if !defined(__GPTBACKEND_ICONV_WRAPPER)
#define __GPTBACKEND_ICONV_WRAPPER 1

#include <string>

#include <iconv.h>

namespace gptbackend {

class iconv_wrapper {
    /* C++ reinterpret_cast<> and static_cast<> can't be used in
     * this case */
    const iconv_t invalid_open = (iconv_t)-1;

    /* Disable copy since iconv_t can't duplicate */
    iconv_wrapper(iconv_wrapper const &) = delete;
    iconv_wrapper &operator=(iconv_wrapper const &) = delete;

    iconv_t conv;
    std::string from_encoding;
    std::string to_encoding;

  public:
    iconv_wrapper(std::string from_encoding, std::string to_encoding);
    ~iconv_wrapper();

    std::string convert(std::string from);
    std::string convert(char *from);

  private:
    void check_conversion_error();
}; /* class iconv_wrapper */

} /* namespace gptbackend */

#endif /* __GPTBACKEND_ICONV_WRAPPER */
