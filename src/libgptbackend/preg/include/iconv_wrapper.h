#if !defined(__GPTBACKEND_ICONV_WRAPPER)
#define __GPTBACKEND_ICONV_WRAPPER 1

#include <string>

#include <iconv.h>

namespace gptbackend {

/**
 * Wrapper for POSIX iconv functionality to ease the access from C++
 * and provide a convenient way to operate on std::string buffers.
 */
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

    /**
     * Convert std::string to another format.
     */
    std::string convert(std::string from);

  private:
    /**
     * Check if there were conversion errors.
     */
    void check_conversion_error();
}; /* class iconv_wrapper */

} /* namespace gptbackend */

#endif /* __GPTBACKEND_ICONV_WRAPPER */
