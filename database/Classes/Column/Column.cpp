#include "Column.h"

#include "ColumnFactory.h"

ColumnCreator::ColumnCreator(ColumnType type) : type(type) {
    ColumnFactory::getFactory().addCreator(*this);
}

ColumnType ColumnCreator::getColumnType() const
{
    return type;
}
