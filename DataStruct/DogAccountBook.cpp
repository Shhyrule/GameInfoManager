// SPDX-License-Identifier: MIT

#include "DogAccountBook.h"
#include <algorithm>

void FDogAccountBook::refresh()
{
    history_import = 0;
    history_import_cost = 0;
    history_export = 0;
    history_real_cost = 0;
    remaining = 0;
    remaining_discount = 1;

    for (FDogABRecord& r : records) {
        switch (r.record_type)
        {
        case ERecordType::EXPORT_TYPE:
            _on_export_added(r);
            break;
        case ERecordType::IMPORT_TYPE:
            _on_import_added(r);
            break;
        default:
            break;
        }
    }
}

void FDogAccountBook::_on_export_added(FDogABRecord& record)
{
    float export_num = record.num;
    history_export += export_num;
    if (export_num > remaining) {
        record.real_num = export_num - remaining + remaining * remaining_discount;
        history_real_cost += record.real_num;
        remaining = 0;
        remaining_discount = 1;
    }
    else {
        record.real_num = export_num * remaining_discount;
        history_real_cost += record.real_num;
        remaining -= export_num;
    }
}

void FDogAccountBook::_on_import_added(const FDogABRecord& record)
{
    history_import += record.num;
    history_import_cost += record.real_num;
    remaining_discount = (remaining * remaining_discount + record.real_num) / (remaining + record.num);
    remaining += record.num;
}

void FDogAccountBook::EraseRecord(const int& id)
{
    auto pos = std::find_if(records.begin(), records.end(), [&](const FDogABRecord& r) {
        return r.id == id;
    });
    if (pos != records.end()) {
        records.erase(pos);
        refresh();
    }
}

FDogABRecord FDogAccountBook::AddImport(const QDate & date, float import, float cost)
{
    FDogABRecord new_record;
    new_record.id = ++max_id;
    new_record.record_type = ERecordType::IMPORT_TYPE;
    new_record.date = date;
    new_record.num = import;
    new_record.real_num = cost;
    if (date < max_date) {
        auto it = std::lower_bound(records.begin(), records.end(),new_record, [&](const FDogABRecord& a, const FDogABRecord& b) {
            return a.date < b.date;
        });
        records.insert(it, new_record);

        refresh();
    }
    else {
        max_date = date;
        records.append(new_record);
        _on_import_added(new_record);
    }
    return new_record;
}

FDogABRecord FDogAccountBook::AddExport(const QDate& date, float export_num)
{
    FDogABRecord new_record;
    new_record.id = ++max_id;
    new_record.record_type = ERecordType::EXPORT_TYPE;
    new_record.date = date;
    new_record.num = export_num;
    if (date < max_date) {
        auto it = std::lower_bound(records.begin(), records.end(), new_record, [&](const FDogABRecord& a, const FDogABRecord& b) {
            return a.date < b.date;
            });
        records.insert(it, new_record);

        refresh();
    }
    else {
        max_date = date;
        _on_export_added(new_record);
        records.append(new_record);
    }
    return new_record;
}

float FDogAccountBook::GetHistoryImportCost() const
{
    return history_import_cost;
}

float FDogAccountBook::GetHistoryExportCost() const
{
    return history_export;
}

float FDogAccountBook::GetHistoryRealCost() const
{
    return history_real_cost;
}

float FDogAccountBook::GetHistoryDiscount() const
{
    return history_import_cost / history_import;
}

float FDogAccountBook::GetRemaining() const
{
    return remaining;
}

float FDogAccountBook::GetCurDiscount() const
{
    return remaining_discount;
}

float FDogAccountBook::GetCut() const
{
    return history_export - history_real_cost;
}

QList<FDogABRecord> FDogAccountBook::GetRecords() const
{
    return records;
}
