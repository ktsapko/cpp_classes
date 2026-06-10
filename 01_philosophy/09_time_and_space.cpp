#include <string>
#include <stdexcept>
#include <cstring>

struct X {
    char ch;
    int i;
    std::string s;

    X& operator=(const X& a);
};

X waste(const char* p)
{
    if (!p) throw std::invalid_argument{"No data."};
    int n = strlen(p);
    auto buf = new (std::nothrow) char[n];
    if (!buf) throw std::bad_alloc{};
    for (int i = 0; i < n; ++i) buf[i] = p[i];
    // ... manipulate buffer ...
    X x;
    x.ch = 'a';
    x.s = std::string(n, '\0');    // give x.s space for *p
    for (size_t i = 0; i < x.s.size(); ++i) x.s[i] = buf[i];  // copy buf into x.s
    delete[] buf;
    return x;
}

void driver()
{
    X x = waste("Typical argument");
    // ...
}



// Yes, this is a caricature, but we have seen every individual mistake in production code, and worse.
// Note that the layout of X guarantees that at least 6 bytes (and most likely more) are wasted. 
// The spurious definition of copy operations disables move semantics so that the return operation is slow
// (please note that the Return Value Optimization, RVO, is not guaranteed here).
// The use of new and delete for buf is redundant; if we really needed a local string, we should use a local string.
// There are several more performance bugs and gratuitous complications.


#include <gsl/gsl>

void lower(gsl::zstring s)
{
    for (int i = 0; i < strlen(s); ++i) s[i] = tolower(s[i]);
}


// This is actually an example from production code.
// We can see that in our condition we have i < strlen(s).
// This expression will be evaluated on every iteration of the loop,
// which means that strlen must walk through every string and loop to discover its length.
// While the string contents are changing, it’s assumed that toLower will not affect the length of the string, 
// so it’s better to cache the length outside the loop and not incur that cost for each iteration.
// Note An individual example of waste is rarely significant, and where it is significant
// it is typically easily eliminated by an expert.
// However, waste spread liberally across a code base can easily be significant 
// and experts are not always as available as we would like.
// The aim of this rule (and the more specific rules that support it) is to eliminate most waste
// related to the use of C++ before it happens. After that, we can look at waste related to algorithms and requirements,
// but that is beyond the scope of these guidelines.
