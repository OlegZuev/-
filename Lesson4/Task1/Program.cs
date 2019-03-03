using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task1 {
    class Program {
        static void Main(string[] args) {
            List<Student> students = new List<Student>();
            for (int j = 0; j < 10; j++) {
                students.Add(new Student($"Студент {j}", "Экономический", 2011 + j, 10 * j));
            }

            List<GraduatedStudent> graduatedStudents = new List<GraduatedStudent>();
            for (int j = 0; j < 10; j++) {
                graduatedStudents.Add(new GraduatedStudent($"Аспирант {j}", "Экономический", 2011 + j, "Кузнецов А. Г.", "05.13.11"));
            }

            List<Student> threeStudents = getThreeSuperStudents(students);
            foreach (var student in threeStudents) {
                student.printInformation();
            }

            List<GraduatedStudent> lastedStudents = getGraduatedStudentsWhoWillEndedEducation(graduatedStudents);
            foreach (var student in lastedStudents) {
                student.printInformation();
            }

            printInformationOfAll(students, graduatedStudents);
        }

        static List<Student> getThreeSuperStudents(List<Student> students) {
            List<Student> copy = new List<Student>(students);
            List<Student> threeStudents = new List<Student>();
            for (int i = 0; i < copy.Count; i++) {
                for (int j = 0; j < copy.Count - i - 1; j++) {
                    if (copy[j].Rating < copy[j + 1].Rating) {
                        Student temp = copy[j];
                        copy[j] = copy[j + 1];
                        copy[j + 1] = temp;
                    }
                }
            }

            for (int i = 0, k = 0; i < copy.Count && k < 3; i++) {
                if (copy[i].Faculty == "Экономический" && copy[i].AdmissionYear == 2019) {
                    threeStudents.Add(copy[i]);
                    k++;
                }
            }

            return threeStudents;
        }

        static List<GraduatedStudent> getGraduatedStudentsWhoWillEndedEducation(List<GraduatedStudent> graduatedStudents) {
            List<GraduatedStudent> result = new List<GraduatedStudent>();
            foreach (var student in graduatedStudents) {
                if (student.SpecialtyCode == "05.13.11" && student.AdmissionYear == 2017) {
                    result.Add(student);
                }
            }

            return result;
        }

        static void printInformationOfAll(List<Student> students, List<GraduatedStudent> graduatedStudents) {
            foreach (var student in students) {
                student.printInformation();
            }
            foreach (var student in graduatedStudents) {
                student.printInformation();
            }
        }
    }

    abstract class Person {
        public string Name { get; }
        public string Faculty { get; }
        public int AdmissionYear { get; }

        protected Person(string name, string faculty, int admissionYear) {
            Name = name;
            Faculty = faculty;
            AdmissionYear = admissionYear;
        }

        public virtual void printInformation() {
            Console.Write("Имя: " + Name + " Факультет: " + Faculty +
                              " Год поступления: " + AdmissionYear);
        }
    }

    class Student : Person {
        public int Rating { get; }
        public Student(string name, string faculty, int admissionYear, int rating) : base(name, faculty, admissionYear) {
            Rating = rating;
        }

        public override void printInformation() {
            base.printInformation();
            Console.WriteLine(" Рейтинг: " + Rating);
        }
    }

    class GraduatedStudent : Person {
        public string Supervisor { get; } 
        public string SpecialtyCode { get; }

        public GraduatedStudent(string name, string faculty, int admissionYear, string supervisor, string specialtyCode) : base(name, faculty, admissionYear) {
            Supervisor = supervisor;
            SpecialtyCode = specialtyCode;
        }

        public override void printInformation() {
            base.printInformation();
            Console.WriteLine(" Руководитель: " + Supervisor + " Код специальности: " + SpecialtyCode);
        }
    } 
}
