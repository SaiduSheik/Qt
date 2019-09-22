import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import Demo 1.0

ColumnLayout {
    Frame {
        Layout.fillWidth: true

        ListView {
            implicitWidth: 250
            implicitHeight: 250
            anchors.fill: parent
            clip: true

            model: DemoModel {
                getSource: source
            }
            delegate: Component {
                Item {
                    width: parent.width
                    height: 40

                    TextField {
                        text: model.id
                        Layout.fillWidth: true
                    }
                    MouseArea {
                                  cursorShape: Qt.PointingHandCursor
                                  anchors.fill: parent
                                  onClicked: source.showDetails(index)
                    }
                }
            }
        }
    }

}
