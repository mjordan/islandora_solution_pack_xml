<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<!--
Simple XSLT stylesheet to transform "flat" XML into simple HTML table markup.
Can be used as the RENDER_STYLESHEET datastream for collections or individual
objects managed by the Islandora Simple XML Solution Pack.
-->

  <xsl:template match="/*">
    <div>
      <table>
        <xsl:apply-templates/>
      </table>
    </div>
  </xsl:template>

  <!-- Select all children of the root node. Human-readable field names
       come from the @displayLabel attribute. -->
  <xsl:template match="*">
    <!-- We don't want to display empty rows. -->
    <xsl:if test="string-length(.) != 0">
      <tr><th><xsl:value-of select="@displayLabel"/></th><td><xsl:value-of select="."/></td></tr>
    </xsl:if>
  </xsl:template>

</xsl:stylesheet>
