import 'dart:io';
import 'dart:convert';
import 'dart:async';

double getAvg(List<String> califications) {
  var total = 0;
  califications.forEach((calification) => total += int.parse(calification));
  return total / califications.length;
}

manageLine(String line, File outFile) {
  final splitedLine = line.split(";");
  double avg = getAvg(splitedLine.sublist(1));
  final rut = splitedLine[0];
  String content = '$rut;$avg\n';
  outFile.writeAsStringSync(content, mode: FileMode.append);
}

Future<void> main(List<String> argv) async {
  try {
    if (argv.isEmpty) {
      throw 'Indique la ruta del archivo';
    }
    final outFile = File('./dart_averages.csv');
    outFile.writeAsString(''); //Resetea el archivo
    var csvPath = argv[0].split("=");
    print('Escribiendo archivo...');
    new File(csvPath[1])
        .openRead()
        .map(utf8.decode)
        .transform(new LineSplitter())
        .forEach((l) => manageLine(l, outFile))
        .catchError(() => throw 'No se pudo abrir el archivo');
  } catch (e) {
    print(e);
  }
}
