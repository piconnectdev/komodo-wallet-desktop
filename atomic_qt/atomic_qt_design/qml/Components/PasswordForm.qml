import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import "../Constants"

ColumnLayout {
    property alias field: input_password.field
    property bool confirm: true

    function isValid() {
        const valid_pw = input_password.isValid()
        if(!confirm) return valid_pw

        const valid_cpw = input_confirm_password.isValid()
        const matching = input_password.field.text === input_confirm_password.field.text
        return valid_pw && valid_cpw && matching

    }

    function reset() {
        input_password.field.text = ""
        input_confirm_password.field.text = ""
    }

    PasswordField {
        id: input_password
        hide_hint: true
    }

    PasswordField {
        visible: confirm
        id: input_confirm_password
        title: qsTr("Confirm Password")
        field.placeholderText: qsTr("Enter the same password to confirm")
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
