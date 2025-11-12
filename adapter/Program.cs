using System;
using System.IO.Pipes;
using System.Speech.Synthesis;

class Program {
    static void Main() {
        Console.WriteLine("ATCTrainer Adapter started.");
        var synth = new SpeechSynthesizer();
        synth.Speak("Adapter online.");

        using (var pipe = new NamedPipeClientStream(".", "ATCTrainerPipe", PipeDirection.InOut)) {
            Console.WriteLine("Connecting to plugin...");
            pipe.Connect();
            Console.WriteLine("Connected.");

            using (var reader = new StreamReader(pipe))
            using (var writer = new StreamWriter(pipe) { AutoFlush = true }) {
                string line;
                while ((line = reader.ReadLine()) != null) {
                    Console.WriteLine("Message: " + line);
                    if (line.Contains("TTS:"))
                        synth.Speak(line.Substring(4));
                }
            }
        }
    }
}
