#pragma once
#include <string>
#include <variant>

namespace lgl {

template<typename T>
class Result {
public:
    static Result ok(T value)              { return Result(OkTag{},  std::move(value)); }
    static Result err(std::string message) { return Result(ErrTag{}, std::move(message)); }

    [[nodiscard]] bool isOk()  const { return m_data.index() == 0; }
    [[nodiscard]] bool isErr() const { return m_data.index() == 1; }

    [[nodiscard]] T&             value() &      { return std::get<0>(m_data); }
    [[nodiscard]] const T&       value() const& { return std::get<0>(m_data); }
    [[nodiscard]] T&&            value() &&     { return std::get<0>(std::move(m_data)); }
    [[nodiscard]] const std::string& error() const { return std::get<1>(m_data); }

    template<typename F>
    auto map(F&& f) -> Result<std::invoke_result_t<F, T>> {
        using U = std::invoke_result_t<F, T>;
        if (isOk()) return Result<U>::ok(f(value()));
        return Result<U>::err(error());
    }

private:
    struct OkTag  {};
    struct ErrTag {};

    explicit Result(OkTag,  T           value) : m_data(std::in_place_index<0>, std::move(value)) {}
    explicit Result(ErrTag, std::string error) : m_data(std::in_place_index<1>, std::move(error)) {}

    std::variant<T, std::string> m_data;
};

template<>
class Result<void> {
public:
    static Result ok()                 { return Result(true);            }
    static Result err(std::string msg) { return Result(std::move(msg));  }

    [[nodiscard]] bool isOk()  const { return m_ok; }
    [[nodiscard]] bool isErr() const { return !m_ok; }
    [[nodiscard]] const std::string& error() const { return m_error; }

private:
    explicit Result(bool)          : m_ok(true)  {}
    explicit Result(std::string e) : m_ok(false), m_error(std::move(e)) {}

    bool        m_ok {false};
    std::string m_error;
};

} 
