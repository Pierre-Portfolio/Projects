Imports System.IO

Public Class Form4
    Dim LesCouleur As Color() = {Color.Red, Color.OrangeRed, Color.Orange, Color.Yellow,
        Color.GreenYellow, Color.LightGreen, Color.SpringGreen, Color.Turquoise,
        Color.DodgerBlue, Color.Blue, Color.MediumSlateBlue, Color.DarkViolet, Color.DeepPink}
    Public nbCouleur As Integer = LesCouleur.Length

    Dim compteur As Integer = 0

    Dim fichiers() As IO.FileInfo
    Dim fichier As IO.FileInfo
    Dim dir As New IO.DirectoryInfo("C:\Users\pierre\Documents\Api center\Codage\Lien")

    Dim filepath1 As String = "C:\Users\pierre\Documents\Api center\Codage\Lien\pnl1.txt"
    Dim filepath2 As String = "C:\Users\pierre\Documents\Api center\Codage\Lien\pnl2.txt"
    Dim filepath3 As String = "C:\Users\pierre\Documents\Api center\Codage\Lien\pnl3.txt"
    Dim filepath4 As String = "C:\Users\pierre\Documents\Api center\Codage\Lien\pnl4.txt"
    Dim filepath5 As String = "C:\Users\pierre\Documents\Api center\Codage\Lien\pnl5.txt"
    Dim filepath6 As String = "C:\Users\pierre\Documents\Api center\Codage\Lien\pnl6.txt"
    Dim filepath7 As String = "C:\Users\pierre\Documents\Api center\Codage\Lien\pnl7.txt"
    Dim filepath8 As String = "C:\Users\pierre\Documents\Api center\Codage\Lien\pnl8.txt"
    Dim filepath9 As String = "C:\Users\pierre\Documents\Api center\Codage\Lien\pnl9.txt"
    Dim filepath10 As String = "C:\Users\pierre\Documents\Api center\Codage\Lien\pnl10.txt"

    Dim Table As New TableLayoutPanel

    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        pnl1.BackgroundImage = My.Resources.Resources.BoutonPlusDeepPink
        pnl2.BackgroundImage = My.Resources.Resources.BoutonPlusDeepPink
        pnl3.BackgroundImage = My.Resources.Resources.BoutonPlusDeepPink
        pnl4.BackgroundImage = My.Resources.Resources.BoutonPlusDeepPink
        pnl5.BackgroundImage = My.Resources.Resources.BoutonPlusDeepPink

        pnl6.BackgroundImage = My.Resources.Resources.BoutonPlusDeepPink
        pnl7.BackgroundImage = My.Resources.Resources.BoutonPlusDeepPink
        pnl8.BackgroundImage = My.Resources.Resources.BoutonPlusDeepPink
        pnl9.BackgroundImage = My.Resources.Resources.BoutonPlusDeepPink
        pnl10.BackgroundImage = My.Resources.Resources.BoutonPlusDeepPink

        Configbouton()
        Tablelayoutpanel()
        Imagepardefault()
        Timer1.Enabled = True
    End Sub

    Dim pnl1 As New Panel
    Dim pnl2 As New Panel
    Dim pnl3 As New Panel
    Dim pnl4 As New Panel
    Dim pnl5 As New Panel
    Dim pnl6 As New Panel
    Dim pnl7 As New Panel
    Dim pnl8 As New Panel
    Dim pnl9 As New Panel
    Dim pnl10 As New Panel

    Private Sub Configbouton()
        pnl1.Height = 42
        pnl1.Width = 40
        pnl2.Size = pnl1.Size
        pnl3.Size = pnl1.Size
        pnl4.Size = pnl1.Size
        pnl5.Size = pnl1.Size
        pnl6.Size = pnl1.Size
        pnl7.Size = pnl1.Size
        pnl8.Size = pnl1.Size
        pnl9.Size = pnl1.Size
        pnl10.Size = pnl1.Size

        AddHandler pnl1.Click, AddressOf Pnl1Action
        AddHandler pnl2.Click, AddressOf Pnl2Action
        AddHandler pnl3.Click, AddressOf Pnl3Action
        AddHandler pnl4.Click, AddressOf Pnl4Action
        AddHandler pnl5.Click, AddressOf Pnl5Action
        AddHandler pnl6.Click, AddressOf Pnl6Action
        AddHandler pnl7.Click, AddressOf Pnl7Action
        AddHandler pnl8.Click, AddressOf Pnl8Action
        AddHandler pnl9.Click, AddressOf Pnl9Action
        AddHandler pnl10.Click, AddressOf Pnl10Action

        pnl1.BackgroundImageLayout = BackgroundImageLayout.Stretch
        pnl2.BackgroundImageLayout = BackgroundImageLayout.Stretch
        pnl3.BackgroundImageLayout = BackgroundImageLayout.Stretch
        pnl4.BackgroundImageLayout = BackgroundImageLayout.Stretch
        pnl5.BackgroundImageLayout = BackgroundImageLayout.Stretch
        pnl6.BackgroundImageLayout = BackgroundImageLayout.Stretch
        pnl7.BackgroundImageLayout = BackgroundImageLayout.Stretch
        pnl8.BackgroundImageLayout = BackgroundImageLayout.Stretch
        pnl9.BackgroundImageLayout = BackgroundImageLayout.Stretch
        pnl10.BackgroundImageLayout = BackgroundImageLayout.Stretch

        Me.Controls.Add(pnl1)
        Me.Controls.Add(pnl2)
        Me.Controls.Add(pnl3)
        Me.Controls.Add(pnl4)
        Me.Controls.Add(pnl5)
        Me.Controls.Add(pnl6)
        Me.Controls.Add(pnl7)
        Me.Controls.Add(pnl8)
        Me.Controls.Add(pnl9)
        Me.Controls.Add(pnl10)
    End Sub

    Dim Imagepnl1 As Boolean = System.IO.File.Exists(filepath1)
    Dim Imagepnl2 As Boolean = System.IO.File.Exists(filepath2)
    Dim Imagepnl3 As Boolean = System.IO.File.Exists(filepath3)
    Dim Imagepnl4 As Boolean = System.IO.File.Exists(filepath4)
    Dim Imagepnl5 As Boolean = System.IO.File.Exists(filepath5)
    Dim Imagepnl6 As Boolean = System.IO.File.Exists(filepath6)
    Dim Imagepnl7 As Boolean = System.IO.File.Exists(filepath7)
    Dim Imagepnl8 As Boolean = System.IO.File.Exists(filepath8)
    Dim Imagepnl9 As Boolean = System.IO.File.Exists(filepath9)
    Dim Imagepnl10 As Boolean = System.IO.File.Exists(filepath10)

    Private Sub Imagepardefault()
        Dim Imagepnl1 As Boolean = System.IO.File.Exists(filepath1)
        Dim Imagepnl2 As Boolean = System.IO.File.Exists(filepath2)
        Dim Imagepnl3 As Boolean = System.IO.File.Exists(filepath3)
        Dim Imagepnl4 As Boolean = System.IO.File.Exists(filepath4)
        Dim Imagepnl5 As Boolean = System.IO.File.Exists(filepath5)
        Dim Imagepnl6 As Boolean = System.IO.File.Exists(filepath6)
        Dim Imagepnl7 As Boolean = System.IO.File.Exists(filepath7)
        Dim Imagepnl8 As Boolean = System.IO.File.Exists(filepath8)
        Dim Imagepnl9 As Boolean = System.IO.File.Exists(filepath9)
        Dim Imagepnl10 As Boolean = System.IO.File.Exists(filepath10)

        Imagepardefault2(Imagepnl1, filepath1, pnl1)
        Imagepardefault2(Imagepnl2, filepath2, pnl2)
        Imagepardefault2(Imagepnl3, filepath3, pnl3)
        Imagepardefault2(Imagepnl4, filepath4, pnl4)
        Imagepardefault2(Imagepnl5, filepath5, pnl5)
        Imagepardefault2(Imagepnl6, filepath6, pnl6)
        Imagepardefault2(Imagepnl7, filepath7, pnl7)
        Imagepardefault2(Imagepnl8, filepath8, pnl8)
        Imagepardefault2(Imagepnl9, filepath9, pnl9)
        Imagepardefault2(Imagepnl10, filepath10, pnl10)
    End Sub

    Private Sub Imagepardefault2(verif As Boolean, verif2 As String, panel1 As Panel)
        Dim compteurLigne As New Integer
        compteurLigne = 0
        If (verif) Then
            For Each line As String In File.ReadLines(verif2)
                If (compteurLigne = 1) Then
                    panel1.BackgroundImage = Image.FromFile(line)
                End If
                compteurLigne += 1
            Next
        End If
    End Sub

    Private Sub Pnl1Action(sender As Object, e As EventArgs)
        Dim openFileDialog1 As New OpenFileDialog
        Dim openFileDialog2 As New OpenFileDialog
        If Not System.IO.File.Exists(filepath1) Then
            Dim osef1 As DialogResult = MessageBox.Show("Choisi le fichier executable", "Important Question")
            Dim result As DialogResult = openFileDialog1.ShowDialog()
            Dim osef2 As DialogResult = MessageBox.Show("Choisi le fichier image", "Important Question")
            Dim result2 As DialogResult = openFileDialog2.ShowDialog()

            If result = Windows.Forms.DialogResult.OK Then
                If result2 = Windows.Forms.DialogResult.OK Then
                    Dim writer As System.IO.StreamWriter = New System.IO.StreamWriter(filepath1)
                    writer.WriteLine(openFileDialog1.FileName)
                    writer.WriteLine(openFileDialog2.FileName)
                    writer.Close()
                    Imagepardefault()
                End If
            Else
                MsgBox("Erreur impossible de selectionner le fichier")
            End If

        Else
            Dim compteurLigne As New Integer
            compteurLigne = 0
            For Each line As String In File.ReadLines(filepath1)
                If (compteurLigne = 0) Then
                    Process.Start(line)
                End If
                compteurLigne += 1
            Next
        End If
    End Sub

    Private Sub Pnl2Action(sender As Object, e As EventArgs)
        Dim openFileDialog1 As New OpenFileDialog
        Dim openFileDialog2 As New OpenFileDialog
        If Not System.IO.File.Exists(filepath2) Then
            MsgBox("Choisi le fichier executable")
            Dim result As DialogResult = openFileDialog1.ShowDialog()
            MsgBox("Choisi le fichier image")
            Dim result2 As DialogResult = openFileDialog2.ShowDialog()

            If result = Windows.Forms.DialogResult.OK Then
                If result2 = Windows.Forms.DialogResult.OK Then
                    Dim writer As System.IO.StreamWriter = New System.IO.StreamWriter(filepath2)
                    writer.WriteLine(openFileDialog1.FileName)
                    writer.WriteLine(openFileDialog2.FileName)
                    writer.Close()
                    Imagepardefault()
                End If
            Else
                MsgBox("Erreur impossible de selectionner le fichier")
            End If

        Else
            Dim compteurLigne As New Integer
            compteurLigne = 0
            For Each line As String In File.ReadLines(filepath2)
                If (compteurLigne = 0) Then
                    Process.Start(line)
                End If
                compteurLigne += 1
            Next
        End If
    End Sub

    Private Sub Pnl3Action(sender As Object, e As EventArgs)
        Dim openFileDialog1 As New OpenFileDialog
        Dim openFileDialog2 As New OpenFileDialog
        If Not System.IO.File.Exists(filepath3) Then
            MsgBox("Choisi le fichier executable")
            Dim result As DialogResult = openFileDialog1.ShowDialog()
            MsgBox("Choisi le fichier image")
            Dim result2 As DialogResult = openFileDialog2.ShowDialog()

            If result = Windows.Forms.DialogResult.OK Then
                If result2 = Windows.Forms.DialogResult.OK Then
                    Dim writer As System.IO.StreamWriter = New System.IO.StreamWriter(filepath3)
                    writer.WriteLine(openFileDialog1.FileName)
                    writer.WriteLine(openFileDialog2.FileName)
                    writer.Close()
                    Imagepardefault()
                End If
            Else
                MsgBox("Erreur impossible de selectionner le fichier")
            End If

        Else
            Dim compteurLigne As New Integer
            compteurLigne = 0
            For Each line As String In File.ReadLines(filepath3)
                If (compteurLigne = 0) Then
                    Process.Start(line)
                End If
                compteurLigne += 1
            Next
        End If
    End Sub

    Private Sub Pnl4Action(sender As Object, e As EventArgs)
        Dim openFileDialog1 As New OpenFileDialog
        Dim openFileDialog2 As New OpenFileDialog
        If Not System.IO.File.Exists(filepath4) Then
            MsgBox("Choisi le fichier executable")
            Dim result As DialogResult = openFileDialog1.ShowDialog()
            MsgBox("Choisi le fichier image")
            Dim result2 As DialogResult = openFileDialog2.ShowDialog()

            If result = Windows.Forms.DialogResult.OK Then
                If result2 = Windows.Forms.DialogResult.OK Then
                    Dim writer As System.IO.StreamWriter = New System.IO.StreamWriter(filepath4)
                    writer.WriteLine(openFileDialog1.FileName)
                    writer.WriteLine(openFileDialog2.FileName)
                    writer.Close()
                    Imagepardefault()
                End If
            Else
                MsgBox("Erreur impossible de selectionner le fichier")
            End If

        Else
            Dim compteurLigne As New Integer
            compteurLigne = 0
            For Each line As String In File.ReadLines(filepath4)
                If (compteurLigne = 0) Then
                    Process.Start(line)
                End If
                compteurLigne += 1
            Next
        End If
    End Sub

    Private Sub Pnl5Action(sender As Object, e As EventArgs)
        Dim openFileDialog1 As New OpenFileDialog
        Dim openFileDialog2 As New OpenFileDialog
        If Not System.IO.File.Exists(filepath5) Then
            MsgBox("Choisi le fichier executable")
            Dim result As DialogResult = openFileDialog1.ShowDialog()
            MsgBox("Choisi le fichier image")
            Dim result2 As DialogResult = openFileDialog2.ShowDialog()

            If result = Windows.Forms.DialogResult.OK Then
                If result2 = Windows.Forms.DialogResult.OK Then
                    Dim writer As System.IO.StreamWriter = New System.IO.StreamWriter(filepath5)
                    writer.WriteLine(openFileDialog1.FileName)
                    writer.WriteLine(openFileDialog2.FileName)
                    writer.Close()
                    Imagepardefault()
                End If
            Else
                MsgBox("Erreur impossible de selectionner le fichier")
            End If

        Else
            Dim compteurLigne As New Integer
            compteurLigne = 0
            For Each line As String In File.ReadLines(filepath5)
                If (compteurLigne = 0) Then
                    Process.Start(line)
                End If
                compteurLigne += 1
            Next
        End If
    End Sub

    Private Sub Pnl6Action(sender As Object, e As EventArgs)
        Dim openFileDialog1 As New OpenFileDialog
        Dim openFileDialog2 As New OpenFileDialog
        If Not System.IO.File.Exists(filepath6) Then
            MsgBox("Choisi le fichier executable")
            Dim result As DialogResult = openFileDialog1.ShowDialog()
            MsgBox("Choisi le fichier image")
            Dim result2 As DialogResult = openFileDialog2.ShowDialog()

            If result = Windows.Forms.DialogResult.OK Then
                If result2 = Windows.Forms.DialogResult.OK Then
                    Dim writer As System.IO.StreamWriter = New System.IO.StreamWriter(filepath6)
                    writer.WriteLine(openFileDialog1.FileName)
                    writer.WriteLine(openFileDialog2.FileName)
                    writer.Close()
                    Imagepardefault()
                End If
            Else
                MsgBox("Erreur impossible de selectionner le fichier")
            End If

        Else
            Dim compteurLigne As New Integer
            compteurLigne = 0
            For Each line As String In File.ReadLines(filepath6)
                If (compteurLigne = 0) Then
                    Process.Start(line)
                End If
                compteurLigne += 1
            Next
        End If
    End Sub

    Private Sub Pnl7Action(sender As Object, e As EventArgs)
        Dim openFileDialog1 As New OpenFileDialog
        Dim openFileDialog2 As New OpenFileDialog
        If Not System.IO.File.Exists(filepath7) Then
            MsgBox("Choisi le fichier executable")
            Dim result As DialogResult = openFileDialog1.ShowDialog()
            MsgBox("Choisi le fichier image")
            Dim result2 As DialogResult = openFileDialog2.ShowDialog()

            If result = Windows.Forms.DialogResult.OK Then
                If result2 = Windows.Forms.DialogResult.OK Then
                    Dim writer As System.IO.StreamWriter = New System.IO.StreamWriter(filepath7)
                    writer.WriteLine(openFileDialog1.FileName)
                    writer.WriteLine(openFileDialog2.FileName)
                    writer.Close()
                    Imagepardefault()
                End If
            Else
                MsgBox("Erreur impossible de selectionner le fichier")
            End If

        Else
            Dim compteurLigne As New Integer
            compteurLigne = 0
            For Each line As String In File.ReadLines(filepath7)
                If (compteurLigne = 0) Then
                    Process.Start(line)
                End If
                compteurLigne += 1
            Next
        End If
    End Sub

    Private Sub Pnl8Action(sender As Object, e As EventArgs)
        Dim openFileDialog1 As New OpenFileDialog
        Dim openFileDialog2 As New OpenFileDialog
        If Not System.IO.File.Exists(filepath8) Then
            MsgBox("Choisi le fichier executable")
            Dim result As DialogResult = openFileDialog1.ShowDialog()
            MsgBox("Choisi le fichier image")
            Dim result2 As DialogResult = openFileDialog2.ShowDialog()

            If result = Windows.Forms.DialogResult.OK Then
                If result2 = Windows.Forms.DialogResult.OK Then
                    Dim writer As System.IO.StreamWriter = New System.IO.StreamWriter(filepath8)
                    writer.WriteLine(openFileDialog1.FileName)
                    writer.WriteLine(openFileDialog2.FileName)
                    writer.Close()
                    Imagepardefault()
                End If
            Else
                MsgBox("Erreur impossible de selectionner le fichier")
            End If

        Else
            Dim compteurLigne As New Integer
            compteurLigne = 0
            For Each line As String In File.ReadLines(filepath8)
                If (compteurLigne = 0) Then
                    Process.Start(line)
                End If
                compteurLigne += 1
            Next
        End If
    End Sub

    Private Sub Pnl9Action(sender As Object, e As EventArgs)
        Dim openFileDialog1 As New OpenFileDialog
        Dim openFileDialog2 As New OpenFileDialog
        If Not System.IO.File.Exists(filepath9) Then
            MsgBox("Choisi le fichier executable")
            Dim result As DialogResult = openFileDialog1.ShowDialog()
            MsgBox("Choisi le fichier image")
            Dim result2 As DialogResult = openFileDialog2.ShowDialog()

            If result = Windows.Forms.DialogResult.OK Then
                If result2 = Windows.Forms.DialogResult.OK Then
                    Dim writer As System.IO.StreamWriter = New System.IO.StreamWriter(filepath9)
                    writer.WriteLine(openFileDialog1.FileName)
                    writer.WriteLine(openFileDialog2.FileName)
                    writer.Close()
                    Imagepardefault()
                End If
            Else
                MsgBox("Erreur impossible de selectionner le fichier")
            End If

        Else
            Dim compteurLigne As New Integer
            compteurLigne = 0
            For Each line As String In File.ReadLines(filepath9)
                If (compteurLigne = 0) Then
                    Process.Start(line)
                End If
                compteurLigne += 1
            Next
        End If
    End Sub

    Private Sub Pnl10Action(sender As Object, e As EventArgs)
        Dim openFileDialog1 As New OpenFileDialog
        Dim openFileDialog2 As New OpenFileDialog
        If Not System.IO.File.Exists(filepath10) Then
            MsgBox("Choisi le fichier executable")
            Dim result As DialogResult = openFileDialog1.ShowDialog()
            MsgBox("Choisi le fichier image")
            Dim result2 As DialogResult = openFileDialog2.ShowDialog()

            If result = Windows.Forms.DialogResult.OK Then
                If result2 = Windows.Forms.DialogResult.OK Then
                    Dim writer As System.IO.StreamWriter = New System.IO.StreamWriter(filepath10)
                    writer.WriteLine(openFileDialog1.FileName)
                    writer.WriteLine(openFileDialog2.FileName)
                    writer.Close()
                    Imagepardefault()
                End If
            Else
                MsgBox("Erreur impossible de selectionner le fichier")
            End If

        Else
            Dim compteurLigne As New Integer
            compteurLigne = 0
            For Each line As String In File.ReadLines(filepath10)
                If (compteurLigne = 0) Then
                    Process.Start(line)
                End If
                compteurLigne += 1
            Next
        End If
    End Sub

    Private Sub Tablelayoutpanel()
        Table.Location = New Drawing.Point(28, 100)
        Table.Size = New Size(232, 95)
        Table.ColumnCount = 5
        Table.RowCount = 2
        Table.BackColor = Color.Transparent
        Table.Controls.Add(pnl1, 0, 0)
        Table.Controls.Add(pnl2, 1, 0)
        Table.Controls.Add(pnl3, 2, 0)
        Table.Controls.Add(pnl4, 3, 0)
        Table.Controls.Add(pnl5, 4, 0)
        Table.Controls.Add(pnl6, 0, 1)
        Table.Controls.Add(pnl7, 1, 1)
        Table.Controls.Add(pnl8, 2, 1)
        Table.Controls.Add(pnl9, 3, 1)
        Table.Controls.Add(pnl10, 4, 1)
        Me.Controls.Add(Table)
    End Sub

    Private Sub ChangerCouleurCollone1(laCouleur As Color)
        Leave.ForeColor = laCouleur
        Reset.ForeColor = laCouleur
    End Sub

    Private Sub ChangerCouleurCollone2(laCouleur As Color)
        FondEscpace.BackColor = laCouleur
        Jeux.ForeColor = laCouleur
    End Sub

    Private Sub ChangerCouleurCollone3(laCouleur As Color)
        TestCouleur(laCouleur, pnl1, filepath1)
        TestCouleur(laCouleur, pnl2, filepath2)
        TestCouleur(laCouleur, pnl3, filepath3)
        TestCouleur(laCouleur, pnl4, filepath4)
        TestCouleur(laCouleur, pnl5, filepath5)
        TestCouleur(laCouleur, pnl6, filepath6)
        TestCouleur(laCouleur, pnl7, filepath7)
        TestCouleur(laCouleur, pnl8, filepath8)
        TestCouleur(laCouleur, pnl9, filepath9)
        TestCouleur(laCouleur, pnl10, filepath10)
    End Sub

    Private Sub TestCouleur(laCouleur As Color, panel As Panel, verif As String)
        If (Not System.IO.File.Exists(verif)) Then
            Select Case laCouleur
                Case Color.Red
                    panel.BackgroundImage = My.Resources.Resources.BoutonPlusRouge
                Case Color.OrangeRed
                    panel.BackgroundImage = My.Resources.Resources.BoutonPlusOrangeRouge
                Case Color.Orange
                    panel.BackgroundImage = My.Resources.Resources.BoutonPlusOrange
                Case Color.Yellow
                    panel.BackgroundImage = My.Resources.Resources.BoutonPlusJaune
                Case Color.GreenYellow
                    panel.BackgroundImage = My.Resources.Resources.BoutonPlusGreenYellow
                Case Color.LightGreen
                    panel.BackgroundImage = My.Resources.Resources.BoutonPlusLightGreen
                Case Color.SpringGreen
                    panel.BackgroundImage = My.Resources.Resources.BoutonPlusSpringGreen
                Case Color.Turquoise
                    panel.BackgroundImage = My.Resources.Resources.BoutonPlusTurquoise
                Case Color.DodgerBlue
                    panel.BackgroundImage = My.Resources.Resources.BoutonPlusDodgerBlue
                Case Color.Blue
                    panel.BackgroundImage = My.Resources.Resources.BoutonPlusBlue
                Case Color.MediumSlateBlue
                    panel.BackgroundImage = My.Resources.Resources.BoutonPlusMediumSlateBlue
                Case Color.DarkViolet
                    panel.BackgroundImage = My.Resources.Resources.BoutonPlusDarkViolet
                Case Color.DeepPink
                    panel.BackgroundImage = My.Resources.Resources.BoutonPlusDeepPink
                Case Else
            End Select
        End If
    End Sub

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick

        ChangerCouleurCollone2(LesCouleur((compteur + 2) Mod nbCouleur))
        ChangerCouleurCollone3(LesCouleur((compteur + 1) Mod nbCouleur))
        ChangerCouleurCollone1(LesCouleur(compteur Mod nbCouleur))

        compteur = compteur + 1
    End Sub

    Private Sub Leave_Click_1(sender As Object, e As EventArgs) Handles Leave.Click
        Form1.Show()
        Me.Hide()
    End Sub

    Private Sub Reset_Click_1(sender As Object, e As EventArgs) Handles Reset.Click
        Dim rep As Integer
        rep = MsgBox("Voulez vous supprimer tout vos raccourcies ?", vbYesNo + vbQuestion, "Attention")
        If rep = vbYes Then
            fichiers = dir.GetFiles("*.txt")
            For Each fichier In fichiers
                fichier.Delete()
            Next
            Imagepardefault()
        Else

        End If
    End Sub
End Class