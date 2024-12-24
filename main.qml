import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import Qt.labs.qmlmodels 1.0
import com.staffmanagementsystem.Employee 1.0

Window {
    id: mainWindow

    height: Screen.width
    width: Screen.width
    visible: true
    title: "Система управления персоналом"

    property var columnWidths: [30, 150, 150, 150, 150, 200, 250, 150, 150, 150, 150, 240, 250]
    property int selectedRow: -1
    property var ids: []
    property int mode: 0 // 0 - creation Employee obj, 1 - editing Employee obj

    ColumnLayout {
        id: mainPanel

        anchors.fill: parent
        spacing: 10

        Rectangle {
            id: controlBar

            Layout.alignment: Qt.AlignTop
            Layout.preferredHeight: parent.height / 4
            Layout.preferredWidth: parent.width
            color: "lightgrey"

            Rectangle {
                id: employeeSection

                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                width: parent.width / 4
                color: "whitesmoke"
                border.color: "black"
                border.width: 1
                radius: 15

                ColumnLayout {
                    spacing: 5
                    anchors.fill: parent
                    anchors.margins: 15

                    Rectangle {
                        Layout.alignment: Qt.AlignTop
                        Layout.preferredHeight: parent.height / 5
                        Layout.preferredWidth: parent.width
                        color: employeeSection.color

                        Text {
                            anchors.centerIn: parent
                            text: "Сотрудники"
                            font.pixelSize: 20
                        }
                    }

                    RoundButton {
                        id: createEmployeeBtn

                        Layout.alignment: Qt.AlignCenter
                        Layout.preferredHeight: parent.height / 4
                        Layout.preferredWidth: parent.width
                        height: parent.height / 4
                        width: employeeSection.width
                        text: "Создать"
                        font.pixelSize: 20
                        onClicked: {
                            mode = 0
                            selectedRow = -1
                            employeeForm.clearForm()
                            employeeForm.visible = true
                        }
                    }

                    RoundButton {
                        id: editEmployeeBtn

                        Layout.alignment: Qt.AlignCenter
                        Layout.preferredHeight: parent.height / 4
                        Layout.preferredWidth: parent.width
                        height: parent.height / 4
                        width: employeeSection.width
                        text: "Редактировать"
                        font.pixelSize: 20
                        enabled: selectedRow === -1 ? false : true
                        onClicked: {
                            mode = 1
                            staffModel.get(selectedRow)
                            employeeForm.visible = true
                            last_name.text = employeeObj.lastName
                            first_name.text = employeeObj.firstName
                            patronymic.text = employeeObj.patronymic
                            position.currentIndex = employeeObj.position
                            department.currentIndex = employeeObj.department
                            official_duties.text = employeeObj.officialDuties
                            document_number.text = employeeObj.docNumber
                            login.text = employeeObj.login
                            setRadioButton(employeeObj.accessLevel)
                            initial_password.text = employeeObj.initialPassword
                            current_password.text = employeeObj.currentPassword
                        }

                        function setRadioButton(accessLevelOption) {
                            if (accessLevelOption === "сотрудник") employeeRadioBtn.checked = true
                            else if (accessLevelOption === "администратор") adminRadioBtn.checked = true
                            else specialRadioBtn.checked = true
                        }
                    }

                    RoundButton {
                        id: deleteEmployeeBtn

                        Layout.alignment: Qt.AlignCenter
                        Layout.preferredHeight: parent.height / 4
                        Layout.preferredWidth: parent.width
                        height: parent.height / 4
                        width: employeeSection.width
                        text: "Удалить"
                        font.pixelSize: 20
                        enabled: selectedRow === -1 ? false : true
                        onClicked: {
                            employeeObj.remove(selectedRow)
                            selectedRow = -1
                        }
                    }
                }
            }
        }

        Item {
            Layout.alignment: Qt.AlignBottom
            Layout.fillHeight: parent.height
            Layout.preferredWidth: parent.width

            TableView {
                id: employeeTableView

                boundsBehavior: Flickable.VerticalFlick
                reuseItems: true
                clip: true

                columnWidthProvider: function (column) {
                    return columnWidths[column]
                }
                topMargin: columnHeaders.implicitHeight
                anchors.fill: parent

                model: staffModel

                delegate: ItemDelegate {
                    height: 50

                    Rectangle {
                        width: parent.width
                        height: parent.height
                        color: index % employeeTableView.rows === selectedRow ? "lightblue" : "white"
                        border.color: "lightgrey"
                        border.width: 1

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                var row = index % employeeTableView.rows
                                selectedRow = (selectedRow === -1 ? row : selectedRow === row ? -1 : row)
                            }
                        }

                        Text {
                            anchors.centerIn: parent
                            text: modelData
                        }
                    }

                    Component.onCompleted: {
                        if (!ids.includes(modelData) && index < employeeTableView.rows) {
                            ids.push(modelData)
                        }
                    }
                }

                Row {
                    id: columnHeaders
                    y: employeeTableView.contentY
                    z: 2

                    Repeater {
                        model: employeeTableView.columns > 0 ? employeeTableView.columns : 1

                        Rectangle {
                            width: employeeTableView.columnWidthProvider(index)
                            height: 25

                            Label {
                                id: labelRow

                                anchors.centerIn: parent
                                text: staffModel.headerData(modelData, Qt.Horizontal)
                                font.bold: true
                            }
                        }
                    }
                }
            }
        }
    }

    Window {
        id: employeeForm

        x: Screen.width / 2 - this.width / 2
        y: Screen.height / 2 - this.height / 2
        width: 500
        height: 800
        title: "Данные сотрудника"
        visible: false

        function clearForm() {
            last_name.text = ""
            first_name.text = ""
            patronymic.text = ""
            position.currentIndex = 0
            department.currentIndex = 0
            official_duties.text = ""
            document_number.text = ""
            login.text = ""
            employeeRadioBtn.checked = true
            initial_password.text = ""
            current_password.text = ""
        }

        Item {
            anchors {
                top: parent.top
                left: parent.left
                right: parent.right
            }
            anchors.margins: 50

            GridLayout {
                id: formLayout

                columns: 2
                rowSpacing: 10
                columnSpacing: 10

                Label {
                    text: "Фамилия:"
                    Layout.fillWidth: true
                }
                TextField {
                    id: last_name

                    Layout.fillWidth: true
                    placeholderText: "Иванов"
                }

                Label {
                    text: "Имя:"
                    Layout.fillWidth: true
                }
                TextField {
                    id: first_name

                    Layout.fillWidth: true
                    placeholderText: "Иван"
                }

                Label {
                    text: "Отчество:"
                    Layout.fillWidth: true
                }
                TextField {
                    id: patronymic

                    Layout.fillWidth: true
                    placeholderText: "Иванович"
                }

                Label {
                    text: "Должность:"
                    Layout.fillWidth: true
                }
                ComboBox {
                    id: position

                    Layout.fillWidth: true
                    model: employeeObj.getPositionsList()
                }

                Label {
                    text: "Подразделение:"
                    Layout.fillWidth: true
                }
                ComboBox {
                    id: department

                    Layout.fillWidth: true
                    model: employeeObj.getDepartmentsList()
                }

                Label {
                    text: "Функции:"
                    Layout.fillWidth: true
                }
                TextField {
                    id: official_duties

                    Layout.fillWidth: true
                    placeholderText: "администрирование"
                }

                Label {
                    text: "Номер документа:"
                    Layout.fillWidth: true
                }
                TextField {
                    id: document_number

                    Layout.fillWidth: true
                    placeholderText: "0000-0000-00ХХХ"
                }

                Label {
                    text: "Уровень доступа:"
                    Layout.fillWidth: true
                }
                ButtonGroup {
                    id: accessLevelBtnGrp
                    buttons: column.children
                }
                Column {
                    id: column
                    RadioButton {
                        id: employeeRadioBtn
                        checked: true
                        text: "сотрудник"
                    }
                    RadioButton {
                        id: adminRadioBtn
                        text: "администратор"
                    }
                    RadioButton {
                        id: specialRadioBtn
                        text: "особый"
                    }
                }

                Label {
                    text: "Логин:"
                    Layout.fillWidth: true
                }
                TextField {
                    id: login

                    Layout.fillWidth: true
                    placeholderText: "IIvanov"
                }

                Label {
                    text: "Первоначальный пароль:"
                    Layout.fillWidth: true
                }
                TextField {
                    id: initial_password

                    Layout.fillWidth: true
                    placeholderText: "XXXXXXXX"
                    readOnly: mode === 0 ? false : true
                    background: Rectangle {
                        id: appearance
                        color: mode === 0 ? "#ffffff" : "lightgrey"
                        border.color: mode === 0 ? "#b0bec5" : "lightgrey"
                    }

                    onFocusChanged:
                    {
                        appearance.border.color = initial_password.activeFocus ? "#0288d1" : "#b0bec5"
                        appearance.border.width = initial_password.activeFocus ? 2 : 1
                    }
                    onTextChanged: {
                        current_password.text = this.text
                    }
                }

                Label {
                    text: "Текущий пароль:"
                    Layout.fillWidth: true
                }
                TextField {
                    id: current_password

                    Layout.fillWidth: true
                    placeholderText: "XXXXXXXX"
                }

                Item { Layout.fillWidth: true }
                Item { Layout.fillWidth: true }

                RoundButton {
                    id: employeeFormSubmit

                    text: "ОК"
                    Layout.fillWidth: true
                    font.pixelSize: 20
                    onClicked: {
                        employeeObj.lastName = last_name.text
                        employeeObj.firstName = first_name.text
                        employeeObj.patronymic = patronymic.text
                        employeeObj.position = position.currentIndex
                        employeeObj.department = department.currentIndex
                        employeeObj.officialDuties = official_duties.text
                        employeeObj.docNumber = document_number.text
                        employeeObj.login = login.text
                        employeeObj.accessLevel = accessLevelBtnGrp.checkedButton.text
                        employeeObj.initialPassword = initial_password.text
                        employeeObj.currentPassword = current_password.text

                        if (mode === 0)
                        {
                            employeeObj.create()
                        }
                        else
                        {
                            employeeObj.update(selectedRow)
                            employeeForm.visible = false
                        }
                        employeeForm.clearForm()
                    }
                }
                RoundButton {
                    id: employeeFormClear

                    text: "Очистить"
                    Layout.fillWidth: true

                    font.pixelSize: 20
                    onClicked: {
                        employeeForm.clearForm()
                    }
                }
            }
        }
    }
}
