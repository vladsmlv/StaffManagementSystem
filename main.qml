import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import Qt.labs.qmlmodels 1.0

Window {
    id: mainWindow

    height: Screen.width
    width: Screen.width
    visible: true
    title: "Staff Management System"

    property var columnWidths: [30, 150, 150, 150, 150, 200, 250, 150, 150, 150, 150, 250]
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

        TableView {
            id: employeeTableView

            boundsBehavior: Flickable.StopAtBounds
            reuseItems: true
            clip: true

            columnWidthProvider: function (column) {
                return columnWidths[column]
            }
            topMargin: columnHeaders.implicitHeight

            Layout.alignment: Qt.AlignBottom
            Layout.fillHeight: parent.height
            Layout.preferredWidth: parent.width

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
                            console.log(ids[selectedRow])
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
                z:2

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
