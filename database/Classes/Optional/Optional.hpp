#pragma once

// replace with boolean "array" in column
template <typename T>
class Optional {
public:
	Optional(const T& value);

	Optional() = default;
	Optional(const Optional& other);
	Optional& operator=(const Optional& other);
	~Optional();

	bool hasValue() const;
	const T& getValue() const;
	void setValue(const T& newValue);
	void reset();
private:
	T* value = nullptr;

	void copyFrom(const Optional& other);
	void free();
};

template<typename T>
Optional<T>::Optional(const T& value)
{
	setValue(value);
}

template<typename T>
Optional<T>::Optional(const Optional<T>& other)
{
	copyFrom(other);
}

template<typename T>
Optional<T>& Optional<T>::operator=(const Optional<T>& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

template<typename T>
Optional<T>::~Optional()
{
	free();
}

template<typename T>
bool Optional<T>::hasValue() const
{
	return value != nullptr;
}

template<typename T>
const T& Optional<T>::getValue() const
{
	return *value;
}

template<typename T>
void Optional<T>::setValue(const T& newValue)
{
	free();
	this->value = new T(newValue);
}

template<typename T>
void Optional<T>::reset()
{
	free();
	value = nullptr;
}

template<typename T>
inline void Optional<T>::copyFrom(const Optional& other)
{
	if (other.hasValue())
	{
		value = new T(*other.value);
	}
	else
	{
		value = nullptr;
	}
}

template<typename T>
inline void Optional<T>::free()
{
	delete value;
}
