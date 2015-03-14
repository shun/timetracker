pragma Singleton
import QtQuick 2.2
import "."

QtObject {
    function cnvDatetimeToString(datetime, format) {
        if (!format) format = 'YYYY-MM-DD hh:mm:ss.SSS';
        format = format.replace(/YYYY/g, datetime.getFullYear());
        format = format.replace(/MM/g, ('0' + (datetime.getMonth() + 1)).slice(-2));
        format = format.replace(/DD/g, ('0' + datetime.getDate()).slice(-2));
        format = format.replace(/hh/g, ('0' + datetime.getHours()).slice(-2));
        format = format.replace(/mm/g, ('0' + datetime.getMinutes()).slice(-2));
        format = format.replace(/ss/g, ('0' + datetime.getSeconds()).slice(-2));
        if (format.match(/S/g)) {
            var milliSeconds = ('00' + datetime.getMilliseconds()).slice(-3);
            var length = format.match(/S/g).length;
            for (var i = 0; i < length; i++) format = format.replace(/S/, milliSeconds.substring(i, i + 1));
        }
        return format;
    }
}
