//
// Created by phatt on 4/13/25.
//

#ifndef UTILITY_H
#define UTILITY_H


#include <QStandardItem>
#include <QList>


inline QList<QStandardItem*> CreateRow(QList<QString> items)
{
    QList<QStandardItem*> row;
    for (const auto& i : items)
        row.append(new QStandardItem(i));
    return row;
}


template <>
struct std::formatter<QString, char> {
    std::formatter<std::string_view, char> base;

    constexpr auto parse(std::format_parse_context& ctx) {
        return base.parse(ctx);  // reuse the base formatter for std::string_view
    }

    template <typename FormatContext>
    auto format(const QString& qstr, FormatContext& ctx) {
        // Convert QString to UTF-8 std::string_view for compatibility
        return base.format(std::string_view(qstr.toUtf8().constData()), ctx);
    }
};

/////////////////////////////////////////////////
/// QDEBUG //////////////////////////////////////
/////////////////////////////////////////////////

inline QDebug operator<<(QDebug dbg, const QStringList& stringList)
{
    dbg.nospace() << "[";
    for (qsizetype i = 0; i < stringList.count(); i++)
    {
        dbg.nospace() << stringList.at(i);
        if (i != stringList.count() - 1)
            dbg.nospace() << ", ";
    }
    dbg.nospace() << "]";
    return dbg;
}
#endif //UTILITY_H

