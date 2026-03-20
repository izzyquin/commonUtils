#include "DataType.h"

DataType::DataType(int d) : data(d) {}

int DataType::getData() const noexcept {
    return data;
}

void DataType::setData(int d) noexcept {
    data = d;
}

bool DataType::operator==(const DataType& d) const noexcept {
    return (this->data == d.getData());
}

std::ostream& operator<<(std::ostream& os, const DataType& obj) {
    os << "{";
    os << obj.getData();
    os << "}";
    return os;
}

bool DataType::operator<(const DataType& other) const noexcept {
    return data < other.data;
}
