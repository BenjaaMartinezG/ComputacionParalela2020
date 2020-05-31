import 'dart:io';
import 'dart:convert';
import 'dart:async';
import 'dart:math';

printScores(String scoreName, Score score) {
  print("\n===${scoreName}===");
  print("Promedio: ${score.average}");
  print("Desviación Estandar: ${score.getStDev()} ");
  print("Moda: ${score.getTrend()}");
  print("Mediana: ${score.getMed()} ");
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
  var totalCount;

  Score() {
    this.uniqueNumbers = new List();
    this.totalViewed = new List();
    this.summedValues = 0;
    this.totalCount = 0;
  }

  set addItem(double item) {
    summedValues += item;
    totalCount += 1;
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

  get average => summedValues / totalCount;
  double getStDev() {
    double average = this.average;
    double variance = 0;
    uniqueNumbers.forEach(
        (uniqueNumber) => variance += pow((uniqueNumber - average), 2.0));
    return sqrt(variance / totalCount);
  }

  double getTrend() {
    int bigestIndex = 0;
    totalViewed.forEach((number) {
      if (number > bigestIndex) {
        bigestIndex = totalViewed.indexOf(number);
      }
    });
    return uniqueNumbers[bigestIndex];
  }

  double getMed() {
    uniqueNumbers.sort();
    int halfIndex = uniqueNumbers.length ~/ 2;
    if (uniqueNumbers.length % 2 == 0) {
      return (uniqueNumbers[halfIndex] + uniqueNumbers[halfIndex - 1]) / 2;
    }
    return uniqueNumbers[halfIndex];
  }
}

Future<void> main(List<String> argv) async {
  try {
    if (argv.isEmpty) {
      throw 'Indique la ruta del archivo';
    }
    var scoreNames = [
      "NEM",
      "RANKING",
      "MATEMATICAS",
      "LENGUAJE",
      "CIENCIAS",
      "HISTORIA",
    ];
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
        .then((l) => scores
            .forEach((index, score) => printScores(scoreNames[index], score)))
        .catchError(() => throw 'No se pudo abrir el archivo');
  } catch (e) {
    print(e);
  }
}
