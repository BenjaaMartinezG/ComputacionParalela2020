import 'dart:io';
import 'dart:convert';
import 'dart:async';

double getAvg(List<String> califications) {
  var total = 0;
  califications.forEach((calification) => total += int.parse(calification));
  return total / califications.length;
}

manageLine(String line, Map scores) {
  final splitedLine = line.split(";");
  final scoresInLine = splitedLine.sublist(1);
  void addScores(index, score) {
    score.addItem = double.parse(scoresInLine[index]);
  }

  scores.forEach(addScores);
}

class Score {
  List<double> uniqueNumbers;
  List<int> totalViewed;
  double summedValues;

  Score() {
    this.uniqueNumbers = new List();
    this.totalViewed = new List();
    this.summedValues = 0;
  }

  set addItem(double item) {
    summedValues += item;
    var index = uniqueNumbers.indexOf(item);
    if (index == -1) {
      //Valor nunca antes visto, se añade a la lista
      uniqueNumbers.add(item);
      totalViewed.add(1);
    } else {
      //Si existe, suma una vista en el item
      totalViewed[index] += 1;
    }
  }
}

Future<void> main(List<String> argv) async {
  try {
    if (argv.isEmpty) {
      throw 'Indique la ruta del archivo';
    }
    var scores = {
      // NEM
      0: Score(),
      // RANKING
      1: Score(),
      // MATH
      2: Score(),
      // LANG
      3: Score(),
      // CIENC
      4: Score(),
      // HIST
      5: Score()
    };
    var csvPath = argv[0].split("=");
    new File(csvPath[1])
        .openRead()
        .map(utf8.decode)
        .transform(new LineSplitter())
        .forEach((l) => manageLine(l, scores))
        .catchError(() => throw 'No se pudo abrir el archivo');
  } catch (e) {
    print(e);
  }
}
