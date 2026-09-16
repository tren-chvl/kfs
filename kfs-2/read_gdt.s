BITS 32
global read_gdtr

read_gdtr:
    mov eax, [esp+4]   ; récupérer l’adresse du buffer passée depuis C
    sgdt [eax]         ; stocker GDTR dans ce buffer
    ret
