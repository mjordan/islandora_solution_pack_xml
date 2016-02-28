<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<!--
Simple XSLT stylesheet to transform "flat" XML into simple HTML table markup.
-->

<!-- Select the root element. -->
<xsl:template match="/*">
  <div>
    <table>
      <xsl:apply-templates/>
    </table>
  </div>
</xsl:template>

<!-- Select all children of the root node. Field names come from @label attributes. -->
<xsl:template match="*">
      <tr><th><xsl:value-of select="@label"/></th><td><xsl:value-of select="."/></td></tr>
</xsl:template>

</xsl:stylesheet>

