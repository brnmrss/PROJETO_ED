                                system("cls");
                                 cout << "\nAlunos Cadastrados: "<< totalAlunos <<" \n";
                                for (int i = 0; i < totalAlunos; i++) {
                                    cout << "Aluno " << i + 1 << ":\n";
                                    cout << "Nome: " << alunosCadastrados[i].nome << "\t";
                                    cout << "Email: " << alunosCadastrados[i].email << "\t";
                                    cout << "Matricula: " << alunosCadastrados[i].matricula << "\t";
                                    cout << "Telefone: " << alunosCadastrados[i].fone << "\t";
                                    cout << "Turma/Serie: " << alunosCadastrados[i].turmaSerie << "\t";

                                    cout << "\n---------------------------------------------------------------\n";
                                }

                                cout << "\n*********************  DELETAR CADASTRO DE ALUNO ************************ \n";
                                cout << "Informe a matrícula do aluno que deseja deletar.\n";
                                cout << "\nMatrícula: ";
                                cin >> alunoDel;

                                int novoTotalAlunos = 0; // Armazena o total de alunos após a exclusão

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
                                    } else {
                                        cout << "Aluno não encontrado para exclusão." << endl;
                                    }
