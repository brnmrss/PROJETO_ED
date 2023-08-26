system("cls");
                                cout << "\n*********************  DELETAR CADASTRO DE ALUNO ************************ \n";
                                cout << "Informe a matrícula do aluno que deseja deletar.\n";
                                cout << "\nMatrícula: \n";
                                cin >> alunoDel;

                                for (int i = 0; i < count; i++){
                                    if (alunoDel == Alu[i].matricula){
                                        if((i+1) < count){
                                        Alu[i] = Alu[i+1];
                                        }
                                    }
                                }
                                count--;
