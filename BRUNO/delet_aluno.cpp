system("cls");
                                cout << "\n*********************  DELETAR CADASTRO DE ALUNO ************************ \n";
                                cout << "Informe a matrícula do aluno que deseja deletar.\n";
                                cout << "\nMatrícula: \n";
                                cin >> alunoDel;

                                int novoTotalAlunos; // Armazena o total de alunos após a exclusão

                                    // Criar um novo array temporário
                                    Aluno novosAlunosCadastrados[ALUNO];

                                    for (int i = 0; i < totalAlunos; i++) {
                                        if (alunoDel != alunosCadastrados[i].matricula) {
                                            novosAlunosCadastrados[novoTotalAlunos] = alunosCadastrados[i];
                                            novoTotalAlunos++;
                                        }
                                    }

                                    if (novoTotalAlunos < totalAlunos) {
                                        // Exclusão bem-sucedida, atualizar o array principal
                                        totalAlunos = novoTotalAlunos;
                                        for (int i = 0; i < totalAlunos; i++) {
                                            alunosCadastrados[i] = novosAlunosCadastrados[i];
                                        }
                                      system("cls");
                                      cout << "exito";
                                      system("pause");
                                    } else {
                                        cout << "Aluno não encontrado para exclusão.";
                                    }
