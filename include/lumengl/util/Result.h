#pragma once
#include <string>
#include <variant>
#include <functional>

namespace lgl {

template<typename T>
class Result {
public:
    static Result ok(T value)              { return Result(std::move(value)); }
    static Result err(std::string message) { return Result(std::move(message)); }

    [[nodiscard]] bool     isOk()    const { return std::holds_alternative<T>(m_data); }
    [[nodiscard]] bool     isErr()   const { return !isOk(); }

    [[nodiscard]] T&                 value() &      { return std::get<T>(m_data); }
    [[nodiscard]] const T&           value() const& { return std::get<T>(m_data); }
    [[nodiscard]] T&&                value() &&     { return std::get<T>(std::move(m_data)); }
    [[nodiscard]] const std::string& error() const  { return std::get<std::string>(m_data); }

    // Monadic helpers
    template<typename F>
    auto map(F&& f) -> Result<std::invoke_result_t<F, T>> {
        using U = std::invoke_result_t<F, T>;
        if (isOk()) return Result<U>::ok(f(value()));
        return Result<U>::err(error());
    }

private:
    explicit Result(T value)           : m_data(std::move(value))   {}
    explicit Result(std::string error) : m_data(std::move(error))   {}

    std::variant<T, std::string> m_data;
};

// Specialization for void success
template<>
class Result<void> {
public:
    static Result ok()                 { return Result(true); }
    static Result err(std::string msg) { return Result(std::move(msg)); }

    [[nodiscard]] bool isOk()  const { return m_ok; }
    [[nodiscard]] bool isErr() const { return !m_ok; }
    [[nodiscard]] const std::string& error() const { return m_error; }

private:
    explicit Result(bool ok)           : m_ok(ok) {}
    explicit Result(std::string error) : m_ok(false), m_error(std::move(error)) {}

    bool        m_ok    {false};
    std::string m_error;
};



} 
