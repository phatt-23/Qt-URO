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


#endif //UTILITY_H

