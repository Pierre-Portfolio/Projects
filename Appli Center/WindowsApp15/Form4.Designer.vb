<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form4
    Inherits System.Windows.Forms.Form

    'Form remplace la méthode Dispose pour nettoyer la liste des composants.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Requise par le Concepteur Windows Form
    Private components As System.ComponentModel.IContainer

    'REMARQUE : la procédure suivante est requise par le Concepteur Windows Form
    'Elle peut être modifiée à l'aide du Concepteur Windows Form.  
    'Ne la modifiez pas à l'aide de l'éditeur de code.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.FondEscpace = New System.Windows.Forms.Panel()
        Me.Jeux = New System.Windows.Forms.Button()
        Me.Reset = New System.Windows.Forms.Button()
        Me.Leave = New System.Windows.Forms.Button()
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        Me.FondEscpace.SuspendLayout()
        Me.SuspendLayout()
        '
        'FondEscpace
        '
        Me.FondEscpace.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
            Or System.Windows.Forms.AnchorStyles.Left) _
            Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.FondEscpace.Controls.Add(Me.Jeux)
        Me.FondEscpace.Location = New System.Drawing.Point(27, 12)
        Me.FondEscpace.Name = "FondEscpace"
        Me.FondEscpace.Size = New System.Drawing.Size(232, 47)
        Me.FondEscpace.TabIndex = 89
        '
        'Jeux
        '
        Me.Jeux.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
            Or System.Windows.Forms.AnchorStyles.Left) _
            Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.Jeux.BackgroundImage = Global.WindowsApp15.My.Resources.Resources.sky_night_space_813269
        Me.Jeux.Font = New System.Drawing.Font("Microsoft Sans Serif", 11.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Jeux.Location = New System.Drawing.Point(1, 3)
        Me.Jeux.Name = "Jeux"
        Me.Jeux.Size = New System.Drawing.Size(229, 42)
        Me.Jeux.TabIndex = 2
        Me.Jeux.Text = "Codage"
        Me.Jeux.UseVisualStyleBackColor = True
        '
        'Reset
        '
        Me.Reset.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
            Or System.Windows.Forms.AnchorStyles.Left) _
            Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.Reset.BackgroundImage = Global.WindowsApp15.My.Resources.Resources.sky_night_space_813269
        Me.Reset.Font = New System.Drawing.Font("Microsoft Sans Serif", 11.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Reset.ForeColor = System.Drawing.SystemColors.ActiveCaptionText
        Me.Reset.Location = New System.Drawing.Point(28, 202)
        Me.Reset.Name = "Reset"
        Me.Reset.Size = New System.Drawing.Size(115, 33)
        Me.Reset.TabIndex = 90
        Me.Reset.Text = "Reset"
        Me.Reset.UseVisualStyleBackColor = True
        '
        'Leave
        '
        Me.Leave.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
            Or System.Windows.Forms.AnchorStyles.Left) _
            Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.Leave.BackgroundImage = Global.WindowsApp15.My.Resources.Resources.sky_night_space_813269
        Me.Leave.Font = New System.Drawing.Font("Microsoft Sans Serif", 11.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Leave.ForeColor = System.Drawing.SystemColors.ActiveCaptionText
        Me.Leave.Location = New System.Drawing.Point(141, 202)
        Me.Leave.Name = "Leave"
        Me.Leave.Size = New System.Drawing.Size(115, 33)
        Me.Leave.TabIndex = 91
        Me.Leave.Text = "Quitter"
        Me.Leave.UseVisualStyleBackColor = True
        '
        'Timer1
        '
        '
        'Form4
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackgroundImage = Global.WindowsApp15.My.Resources.Resources._4494276_galaxy_wallpapers_hd
        Me.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch
        Me.ClientSize = New System.Drawing.Size(284, 258)
        Me.Controls.Add(Me.Leave)
        Me.Controls.Add(Me.Reset)
        Me.Controls.Add(Me.FondEscpace)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow
        Me.Name = "Form4"
        Me.Text = "Codage"
        Me.FondEscpace.ResumeLayout(False)
        Me.ResumeLayout(False)

    End Sub

    Friend WithEvents FondEscpace As Panel
    Friend WithEvents Jeux As Button
    Friend WithEvents Reset As Button
    Friend WithEvents Leave As Button
    Friend WithEvents Timer1 As Timer
End Class
