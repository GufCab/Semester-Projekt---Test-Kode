﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using test_dll;

namespace test_console
{
    class Program
    {
        static void Main(string[] args)
        {
            Class1 c = new Class1();
            c.func();
            Console.ReadLine();
        }
    }
}
