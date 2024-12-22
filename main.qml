import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import Qt.labs.qmlmodels 1.0
import com.staffmanagementsystem.Employee 1.0
// import com.staffmanagementsystem.StaffDBModel 1.0

Window {
    id: mainWindow

    height: Screen.width
    width: Screen.width
    visible: true
    title: "Staff Management System"

    property var columnWidths: [30, 150, 150, 150, 150, 200, 250, 150, 150, 150, 150, 240, 250]
    property int selectedRow: -1
    property var ids: []

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
                        id: createEmployee

                        Layout.alignment: Qt.AlignCenter
                        Layout.preferredHeight: parent.height / 4
                        Layout.preferredWidth: parent.width
                        height: parent.height / 4
                        width: employeeSection.width
                        text: "Создать"
                        font.pixelSize: 20
                        onClicked: {
                            createEmployeeForm.visible = true
                        }
                    }

                    RoundButton {
                        id: editEmployee

                        Layout.alignment: Qt.AlignCenter
                        Layout.preferredHeight: parent.height / 4
                        Layout.preferredWidth: parent.width
                        height: parent.height / 4
                        width: employeeSection.width
                        text: "Редактировать"
                        font.pixelSize: 20
                        enabled: selectedRow === -1 ? false : true
                    }

                    RoundButton {
                        id: deleteEmployee

                        Layout.alignment: Qt.AlignCenter
                        Layout.preferredHeight: parent.height / 4
                        Layout.preferredWidth: parent.width
                        height: parent.height / 4
                        width: employeeSection.width
                        text: "Удалить"
                        font.pixelSize: 20
                        enabled: selectedRow === -1 ? false : true
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
                        border.color: "black"
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
        id: createEmployeeForm

        x: Screen.width / 2 - this.width / 2
        y: Screen.height / 2 - this.height / 2
        width: 500
        height: 800
        visible: false

        Employee {
            id: employee
        }

        // StaffDBModel {
        //     id: tableModelEntity
        // }



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
                    text: "Логин:"
                    Layout.fillWidth: true
                }
                TextField {
                    id: login

                    Layout.fillWidth: true
                    placeholderText: "IIvanov"
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
                        checked: true
                        text: "сотрудник"
                    }
                    RadioButton {
                        text: "администратор"
                    }
                    RadioButton {
                        text: "особый"
                    }
                }

                Label {
                    text: "Первоначальный пароль:"
                    Layout.fillWidth: true
                }
                TextField {
                    id: initial_password

                    Layout.fillWidth: true
                    placeholderText: "XXXXXXXX"
                }

                Item { Layout.fillWidth: true }
                Item { Layout.fillWidth: true }

                RoundButton {
                    id: createEmployeeFormSubmit

                    text: "ОК"
                    Layout.fillWidth: true
                    font.pixelSize: 20
                    onClicked: {
                        // employee.lastName = last_name.text
                        // employee.firstName = first_name.text
                        // employee.patronymic = patronymic.text
                        // employee.position = position.currentText
                        // employee.department = department.currentText
                        // employee.officialDuties = official_duties.text
                        // employee.docNumber = document_number.text
                        // employee.login = login.text
                        // employee.accessLevel = accessLevelBtnGrp.checkedButton.text
                        // employee.initialPassword = initial_password.text

                        // tableModelEntity.create(employee)

                        employeeObj.lastName = last_name.text
                        employeeObj.firstName = first_name.text
                        employeeObj.patronymic = patronymic.text
                        employeeObj.position = position.currentText
                        employeeObj.department = department.currentText
                        employeeObj.officialDuties = official_duties.text
                        employeeObj.docNumber = document_number.text
                        employeeObj.login = login.text
                        employeeObj.accessLevel = accessLevelBtnGrp.checkedButton.text
                        employeeObj.initialPassword = initial_password.text

                        employeeObj.submit()
                    }
                }
                RoundButton {
                    id: clearEmployeeFormSubmit

                    text: "Очистить"
                    Layout.fillWidth: true

                    font.pixelSize: 20
                    onClicked: {

                    }
                }
            }
        }
    }
}
