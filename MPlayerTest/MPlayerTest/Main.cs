using System;
using System.Threading;
using System.Diagnostics;
using System.IO;

namespace MPlayerTest
{
	class MainClass
	{
		static public StreamReader OutTestStr;

		public static void Main (string[] args)
		{
			string path = "Jump.mp3";

			var _mplayer = new Process ();
			var startInfo = new ProcessStartInfo ();

			string arguments = "-idle -quiet -slave ";// + path;  

			startInfo.FileName = "mplayer";
			startInfo.Arguments = arguments;

			startInfo.RedirectStandardError = true;
			startInfo.RedirectStandardInput = true;
			startInfo.RedirectStandardOutput = true;

			startInfo.UseShellExecute = false;

			_mplayer.StartInfo = startInfo;

			_mplayer.Start ();
			OutTestStr = _mplayer.StandardOutput;
			StreamWriter InTestStr = _mplayer.StandardInput;
			string userInput = "";

			Thread writeThread = new Thread(ThreadFunc);
			writeThread.Start();
			while (true) 
			{
				userInput = Console.ReadLine();

				if(userInput == "p")
					InTestStr.WriteLine("pause");

				if(userInput == "t")
					InTestStr.WriteLine("get_time_pos");

				if(userInput == "l")
					InTestStr.WriteLine("loadfile Jump.mp3");
			}
		}

		private static void ThreadFunc ()
		{
			//string[] ThrInput = new string[2];
			while (true) 
			{
				if(OutTestStr.Peek() >= 0)
				{
					string str = OutTestStr.ReadLine();
					string[] strArr = str.Split('=');
					int length = strArr.Length;

					string second = strArr[length - 1];

					//Console.WriteLine(str);
					Console.WriteLine(second);

				}
			}
		}
	}


}
