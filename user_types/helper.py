from datetime import date

# C++ sys_days uses 1970-01-01 as the epoch
# however, datetime.date uses 0000-01-01 as the epoch
# so we need to add the number of days between these:
#
# This value is datetime.date(1970, 1, 1).toordinal()
DAYS_TO_EPOCH = date(1970, 1, 1).toordinal()

def print_date(valobj, internal_dict, options) -> str:
    m_days = valobj.GetChildMemberWithName("days_").GetValueAsSigned()
    py_date = date.fromordinal(DAYS_TO_EPOCH + m_days)
    return f"date: {py_date}"


class SpanProvider:
    def __init__(self, valobj, internal_dict):
        self.valobj = valobj

    # Give python the _number_ of children in the container
    def num_children(self, max_children) -> int:
        # Get the count_ member from the span
        return self.valobj.GetChildMemberWithName("count_").unsigned

    # Get a child within the container
    def get_child_at_index(self, index):
        return self.valobj.GetValueForExpressionPath(f".data_[{index}]")


def __lldb_init_module(debugger, internal_dict):
    debugger.HandleCommand(
        "type summary add --python-function helper.print_date example::date"
    )
    debugger.HandleCommand(
        'type synthetic add -x "example::span<" --python-class helper.SpanProvider'
    )
    debugger.HandleCommand(
        'type summary add --expand -x "example::span<" --summary-string "${svar%#} items"'
    )
